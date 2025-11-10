#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"

#include <System.SysUtils.hpp>
#include <memory>

#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;

// ===================== AST & Parser (Unicode) =====================
namespace {

class Telement {
protected:
    Telement* left;
    Telement* right;
public:
    Telement(Telement* L, Telement* R) : left(L), right(R) {}
    virtual ~Telement() { delete left; delete right; }
    virtual double rezult() = 0;
    virtual Telement* copy() = 0;
    virtual Telement* differ() = 0;
    virtual void set_var(double X) {
        if (left)  left->set_var(X);
        if (right) right->set_var(X);
    }
};

class Real : public Telement {
    double f;
public:
    Real(double F) : Telement(nullptr, nullptr), f(F) {}
    double rezult() override { return f; }
    Telement* copy() override { return new Real(f); }
    Telement* differ() override { return new Real(0.0); }
};

class Var : public Telement {
    double x;
public:
    Var(double X = 0.0) : Telement(nullptr, nullptr), x(X) {}
    double rezult() override { return x; }
    Telement* copy() override { return new Var(x); }
    Telement* differ() override { return new Real(1.0); }
    void set_var(double X) override { x = X; }
};

struct Plus : public Telement {
    Plus(Telement* L, Telement* R) : Telement(L, R) {}
    double rezult() override { return left->rezult() + right->rezult(); }
    Telement* copy() override { return new Plus(left->copy(), right->copy()); }
    Telement* differ() override { return new Plus(left->differ(), right->differ()); }
};

struct Minus : public Telement {
    Minus(Telement* L, Telement* R) : Telement(L, R) {}
    double rezult() override { return left->rezult() - right->rezult(); }
    Telement* copy() override { return new Minus(left->copy(), right->copy()); }
    Telement* differ() override { return new Minus(left->differ(), right->differ()); }
};

struct Mult : public Telement {
    Mult(Telement* L, Telement* R) : Telement(L, R) {}
    double rezult() override { return left->rezult() * right->rezult(); }
    Telement* copy() override { return new Mult(left->copy(), right->copy()); }
    Telement* differ() override {
        return new Plus(
            new Mult(left->differ(), right->copy()),
            new Mult(left->copy(),  right->differ())
        );
    }
};

struct Div : public Telement {
    Div(Telement* L, Telement* R) : Telement(L, R) {}
    double rezult() override { return left->rezult() / right->rezult(); }
    Telement* copy() override { return new Div(left->copy(), right->copy()); }
    Telement* differ() override {
        return new Div(
            new Minus(
                new Mult(left->differ(), right->copy()),
                new Mult(left->copy(),   right->differ())
            ),
            new Mult(right->copy(), right->copy())
        );
    }
};

// reverse search (1-based pos from end), 0 if not found
int PosFromEnd(const UnicodeString& s, const UnicodeString& sub)
{
    const int l = s.Length();
    UnicodeString p; p.SetLength(l);
    for (int i = 1; i <= l; ++i) p[l - i + 1] = s[i]; // reverse s
    const int pos = p.Pos(sub);
    return (pos > 0) ? (l - pos + 1) : 0;
}

// remove spaces/tabs/newlines
UnicodeString StripSpaces(const UnicodeString& s)
{
    UnicodeString out; out.SetLength(s.Length());
    int j = 0;
    for (int i = 1; i <= s.Length(); ++i) {
        const wchar_t c = s[i];
        if (c != L' ' && c != L'\t' && c != L'\r' && c != L'\n') {
            out[++j] = c;
        }
    }
    out.SetLength(j);
    return out;
}

Telement* form(const UnicodeString& raw)
{
    const UnicodeString s = StripSpaces(raw);
    const int l = s.Length();
    int p;

    if ((p = PosFromEnd(s, L"+")) > 1)
        return new Plus(form(s.SubString(1, p - 1)), form(s.SubString(p + 1, l - p)));
    else if ((p = PosFromEnd(s, L"-")) > 1)
        return new Minus(form(s.SubString(1, p - 1)), form(s.SubString(p + 1, l - p)));
    else if ((p = PosFromEnd(s, L"*")) > 1)
        return new Mult(form(s.SubString(1, p - 1)), form(s.SubString(p + 1, l - p)));
    else if ((p = PosFromEnd(s, L"/")) > 1)
        return new Div(form(s.SubString(1, p - 1)), form(s.SubString(p + 1, l - p)));
    else if (s.Trim().LowerCase() == L"x")
        return new Var();
    else
        return new Real(StrToFloat(s)); // respects OS locale decimal separator
}

} // namespace
// ===================== /AST & Parser =====================

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    // Гарантована підтримка кирилиці
    Font->Name = L"Segoe UI";
    Font->Size = 9;

    Caption                   = L"Політ ракети";
    GroupBoxModel->Caption    = L"Математична модель";
    GroupBoxResults->Caption  = L"Результати обчислення";

    Label1->Caption = L"час";
    Label2->Caption = L"шлях";

    Label3->Caption = L"x";
    Label4->Caption = L"шлях";
    Label5->Caption = L"швидкість";
    Label6->Caption = L"прискорення";

    Label7->Caption = L"Точність";
    Label8->Caption = L"Знаки після десяткової крапки";

    ButtonCompute->Caption = L"Обчислити";
    ButtonExit->Caption    = L"Вихід";

    if (ComboBox1->Items->Count == 0) {
        ComboBox1->Items->Add(L"0");
        ComboBox1->Items->Add(L"1");
        ComboBox1->Items->Add(L"2");
        ComboBox1->Items->Add(L"3");
        ComboBox1->Items->Add(L"4");
        ComboBox1->Items->Add(L"5");
        ComboBox1->ItemIndex = 3; // за замовчуванням: 3 знаки
    }

    // Початкові значення як на прикладі:
    Edit1->Text = L"2.581,2?"; // <-- якщо у вас крапка як десятковий роздільник, просто лишіть "2"
    Edit1->Text = L"2";
    Edit2->Text = L"3*x*x-2*x+5";
}";
}

void __fastcall TForm1::ButtonComputeClick(TObject *Sender)
{
    try {
        std::unique_ptr<Telement> x(form(Edit1->Text));
        std::unique_ptr<Telement> f(form(Edit2->Text));

        std::unique_ptr<Telement> f1(f->differ());  // f'(x)
        std::unique_ptr<Telement> f2(f1->differ()); // f''(x)

        const double X = x->rezult();
        f->set_var(X);
        f1->set_var(X);
        f2->set_var(X);

        const int precision = 15;
        const int digits = StrToIntDef(ComboBox1->Text, 3);

        Edit3->Text = FloatToStrF(X,            ffFixed, precision, digits);
        Edit4->Text = FloatToStrF(f->rezult(),  ffFixed, precision, digits);
        Edit5->Text = FloatToStrF(f1->rezult(), ffFixed, precision, digits);
        Edit6->Text = FloatToStrF(f2->rezult(), ffFixed, precision, digits);
    }
    catch (...) {
        Application->MessageBox(
            L"Input error. Use only +, -, *, /, real numbers and variable x (no parentheses).",
            L"Error", MB_OK | MB_ICONERROR);
    }
}

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
    ButtonComputeClick(ButtonCompute);
}

void __fastcall TForm1::ButtonExitClick(TObject *Sender)
{
    Close();
}
