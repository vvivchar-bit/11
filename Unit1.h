fndef Unit1H
#define Unit1H

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

class TForm1 : public TForm
{
__published: // IDE-managed
    // === Групи ===
    TGroupBox *GroupBoxModel;    // "Математична модель"
    TGroupBox *GroupBoxResults;  // "Результати обчислення"

    // === Модель (усередині GroupBoxModel) ===
    TLabel *Label1;   // "час"
    TLabel *Label2;   // "шлях"
    TEdit  *Edit1;    // input: x (час)
    TEdit  *Edit2;    // input: f(x) (шлях)

    // === Результати (усередині GroupBoxResults) ===
    TLabel *Label3;   // "x"
    TLabel *Label4;   // "шлях"
    TLabel *Label5;   // "швидкість"
    TLabel *Label6;   // "прискорення"
    TEdit  *Edit3;    // output x
    TEdit  *Edit4;    // output f(x)
    TEdit  *Edit5;    // output f'(x)
    TEdit  *Edit6;    // output f''(x)

    // === Точність ===
    TLabel    *Label7;    // "Точність"
    TLabel    *Label8;    // "Знаки після десяткової крапки"
    TComboBox *ComboBox1; // digits after decimal

    // === Кнопки ===
    TButton *ButtonCompute; // "Обчислити"
    TButton *ButtonExit;    // "Вихід"

    // Події
    void __fastcall ButtonComputeClick(TObject *Sender);
    void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall ButtonExitClick(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);

public:
    __fastcall TForm1(TComponent* Owner);
};

extern PACKAGE TForm1 *Form1;
#endif
