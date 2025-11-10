object Form1: TForm1
  Left = 200
  Top = 120
  Caption = #1056#1119#1056#1109#1056#187#1057#8211#1057#8218' '#1057#1026#1056#176#1056#1108#1056#181#1057#8218#1056#1105
  ClientHeight = 360
  ClientWidth = 520
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  TextHeight = 17
  object Label7: TLabel
    Left = 16
    Top = 268
    Width = 114
    Height = 17
    Caption = #1056#1118#1056#1109#1057#8225#1056#1029#1057#8211#1057#1027#1057#8218#1057#1034
  end
  object Label8: TLabel
    Left = 80
    Top = 292
    Width = 373
    Height = 17
    Caption = #1056#8212#1056#1029#1056#176#1056#1108#1056#1105' '#1056#1111#1057#8211#1057#1027#1056#187#1057#1039' '#1056#1169#1056#181#1057#1027#1057#1039#1057#8218#1056#1108#1056#1109#1056#1030#1056#1109#1057#8212' '#1056#1108#1057#1026#1056#176#1056#1111#1056#1108#1056#1105
  end
  object GroupBoxModel: TGroupBox
    Left = 16
    Top = 12
    Width = 488
    Height = 88
    Caption = #1056#1114#1056#176#1057#8218#1056#181#1056#1112#1056#176#1057#8218#1056#1105#1057#8225#1056#1029#1056#176' '#1056#1112#1056#1109#1056#1169#1056#181#1056#187#1057#1034
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 28
      Width = 39
      Height = 17
      Caption = #1057#8225#1056#176#1057#1027
    end
    object Label2: TLabel
      Left = 16
      Top = 56
      Width = 63
      Height = 17
      Caption = #1057#8364#1056#187#1057#1039#1057#8230
    end
    object Edit1: TEdit
      Left = 80
      Top = 24
      Width = 376
      Height = 25
      TabOrder = 0
    end
    object Edit2: TEdit
      Left = 80
      Top = 52
      Width = 376
      Height = 25
      TabOrder = 1
    end
  end
  object GroupBoxResults: TGroupBox
    Left = 16
    Top = 112
    Width = 488
    Height = 144
    Caption = #1056#160#1056#181#1056#183#1057#1107#1056#187#1057#1034#1057#8218#1056#176#1057#8218#1056#1105' '#1056#1109#1056#177#1057#8225#1056#1105#1057#1027#1056#187#1056#181#1056#1029#1056#1029#1057#1039
    TabOrder = 1
    object Label3: TLabel
      Left = 16
      Top = 28
      Width = 6
      Height = 17
      Caption = 'x'
    end
    object Label4: TLabel
      Left = 16
      Top = 56
      Width = 63
      Height = 17
      Caption = #1057#8364#1056#187#1057#1039#1057#8230
    end
    object Label5: TLabel
      Left = 16
      Top = 84
      Width = 125
      Height = 17
      Caption = #1057#8364#1056#1030#1056#1105#1056#1169#1056#1108#1057#8211#1057#1027#1057#8218#1057#1034
    end
    object Label6: TLabel
      Left = 16
      Top = 112
      Width = 158
      Height = 17
      Caption = #1056#1111#1057#1026#1056#1105#1057#1027#1056#1108#1056#1109#1057#1026#1056#181#1056#1029#1056#1029#1057#1039
    end
    object Edit3: TEdit
      Left = 120
      Top = 24
      Width = 200
      Height = 25
      ReadOnly = True
      TabOrder = 0
    end
    object Edit4: TEdit
      Left = 120
      Top = 52
      Width = 200
      Height = 25
      ReadOnly = True
      TabOrder = 1
    end
    object Edit5: TEdit
      Left = 120
      Top = 80
      Width = 200
      Height = 25
      ReadOnly = True
      TabOrder = 2
    end
    object Edit6: TEdit
      Left = 120
      Top = 108
      Width = 200
      Height = 25
      ReadOnly = True
      TabOrder = 3
    end
  end
  object ComboBox1: TComboBox
    Left = 16
    Top = 288
    Width = 56
    Height = 25
    Style = csDropDownList
    TabOrder = 2
    OnChange = ComboBox1Change
  end
  object ButtonCompute: TButton
    Left = 272
    Top = 320
    Width = 112
    Height = 28
    Caption = #1056#1115#1056#177#1057#8225#1056#1105#1057#1027#1056#187#1056#1105#1057#8218#1056#1105
    TabOrder = 3
    OnClick = ButtonComputeClick
  end
  object ButtonExit: TButton
    Left = 392
    Top = 320
    Width = 112
    Height = 28
    Caption = #1056#8217#1056#1105#1057#8230#1057#8211#1056#1169
    TabOrder = 4
    OnClick = ButtonExitClick
  end
end
