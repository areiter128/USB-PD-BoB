Attribute VB_Name = "modCodeGeneration"
Option Explicit

Private Const FILE_COMMENT_START As String = _
    "/* ***********************************************************************************************" & vbCrLf & _
    " * File:        %BOARD_LABEL%_pinmap.h                                                             " & vbCrLf & _
    " * Author:      %USERNAME%                                                                         " & vbCrLf & _
    " * Comments:    Hardware abstraction layer device pinout descriptor                                " & vbCrLf & _
    " * Board ID:    %BOARD_NAME%                                                                       " & vbCrLf & _
    " * Date:        %DATE%                                                                             " & vbCrLf & _
    " * Build:       %FILE_BUILD%                                                                       " & vbCrLf

Private Const FILE_COMMENT_DESCRIPTION As String = _
    " *                                                                                                 " & vbCrLf & _
    " * Description:                                                                                    " & vbCrLf & _
    " * This is a header file template adding signal labels for the hardware abstraction layer          " & vbCrLf & _
    " * In this example user defined signals are directly associated to specific device pins.           " & vbCrLf & _
    " * These associations have been created using the MS Excel macro-based code generation tool        " & vbCrLf & _
    " * MyBoard_RXX_pinout.xlsm located in the h/hal/config directory of the project.                   " & vbCrLf & _
    " *                                                                                                 " & vbCrLf

Private Const FILE_COMMENT_NOTE As String = _
    " * Note:                                                                                           " & vbCrLf & _
    " * This file is the junction point between hardware and microcontroller abstraction layer.         " & vbCrLf & _
    " * To better separate them from each other (e.g. for supporting CPU cards in hardware platforms),  " & vbCrLf & _
    " * generic signal labels may be used in these declarations, which can be used to associate MCU     " & vbCrLf & _
    " * device pins in MCAL to signals defined in HAL.                                                  " & vbCrLf

Private Const FILE_COMMENT_EXAMPLE_A As String = _
    " *                                                                                     " & vbCrLf & _
    " * EXAMPLE OF BOTH USE CASES                                                           " & vbCrLf & _
    " *                                                                                     " & vbCrLf & _
    " * a) Direct pin assignment using ONE header file in HAL                               " & vbCrLf & _
    " *                                                                                     " & vbCrLf & _
    " *  File:       MyBoard_RXX_pinmap.h                                                   " & vbCrLf & _
    " * -----------------------------------------------------------------------             " & vbCrLf & _
    " *                                                                                     " & vbCrLf & _
    " *              #define CLKOUT  _LATB1                                                 " & vbCrLf & _
    " *                                                                                     " & vbCrLf & _
    " * Any usage of the label CLKOUT in user code will automatically be mapped to the      " & vbCrLf & _
    " * specific device pin RB1. Thus board hardware and MCU itself become independent,     " & vbCrLf & _
    " * exchangeable elements in the firmware and pin-out changes made won't affect         " & vbCrLf & _
    " * the rest of the firmware.                                                           " & vbCrLf & _
    " *                                                                                     " & vbCrLf & _
    " * However, although this assignment simplifies the hardware abstraction, HAL and MCAL " & vbCrLf & _
    " * are not clearly separated as MCU specific registers are assigned here.              " & vbCrLf & _
    " *                                                                                     " & vbCrLf

Private Const FILE_COMMENT_EXAMPLE_B As String = _
    " *                                                                                     " & vbCrLf & _
    " * b) Indirect pin assignment using TWO header files in HAL and MCAL                   " & vbCrLf & _
    " *          " & vbCrLf & _
    " *  File:       MyBoard_RXX_pinmap.h            MyController_pinmap.h                  " & vbCrLf & _
    " * -----------------------------------------------------------------------             " & vbCrLf & _
    " *          " & vbCrLf & _
    " *              #define CLKOUT  TP08            #define TP08    _LATB1                 " & vbCrLf & _
    " *     " & vbCrLf & _
    " * Any usage of the label CLKOUT in user code will automatically be mapped to the          " & vbCrLf & _
    " * specific device pin RB1. Thus board hardware, MCU adapter card and MCU itself become    " & vbCrLf & _
    " * independent, exchangeable elements in the firmware and changes made here won't affect   " & vbCrLf & _
    " * the rest of the firmware.                                                           " & vbCrLf & _
    " *                                                                                     " & vbCrLf & _
    " * This functional assignment scheme clearly separates HAL and MCAL, but adds more complexity  " & vbCrLf & _
    " * to the structure. This scheme works best when working with CPU adapter cards like   " & vbCrLf & _
    " * Microchip's Digital Power Plug-In Modules.                                          " & vbCrLf & _
    " *                                                                                     " & vbCrLf & _
    " *                                                                                     " & vbCrLf

Private Const FILE_COMMENT_END As String = _
    " * ***********************************************************************************************/    " & vbCrLf

Private Const MCAL_INCLUDE_PATH As String = "mcal/mcal.h"

Private Const FILE_INCLUSIONS As String = _
    "#include <xc.h> // include processor files - each processor file is guarded " & vbCrLf & _
    "#include <stdint.h> // Include standard integer types                       " & vbCrLf & _
    "#include <stdbool.h> // Include standard boolean types                      " & vbCrLf & _
    "#include %MCAL_INCLUDE_PATH% // Include local mcal layer header file        " & vbCrLf & _
    vbCrLf

Private Const PINMAP_VERSION_COMMENT As String = _
    "/* @@PNMAP_VERSION" & vbCrLf & _
    " * ***********************************************************************************************" & vbCrLf & _
    " * Description:" & vbCrLf & _
    " * This flag is a user defined flag helping to provide version information about the" & vbCrLf & _
    " * pinmap file. This string can be used universally across the firmware to identify the" & vbCrLf & _
    " * hardware version this firmaware was written for." & vbCrLf & _
    " *" & vbCrLf & _
    " * Please Note:" & vbCrLf & _
    " * His label is not connected to the generic macro specified in the compiler settings" & vbCrLf & _
    " * and need to maintained by the designer independently." & vbCrLf & _
    " * ***********************************************************************************************/" & vbCrLf & _
    vbCrLf
 
Private Const COMMENT_SEPARATOR As String = _
    vbCrLf & "/* ***********************************************************************************************/" & vbCrLf

Private Const GUARD_CONDITION As String = _
"// This is a guard condition so that contents of this file are not included" & vbCrLf & _
"// more than once." & vbCrLf

' info section definition
Private Const ROW_CORE_TYPE As Long = 2
Private Const COL_CORE_TYPE As Long = 2

Private Const ROW_BOARD_NAME As Long = 3
Private Const COL_BOARD_NAME As Long = 2

Private Const ROW_VERSION As Long = 4
Private Const COL_VERSION As Long = 2

Private Const ROW_CONTRIBUTOR As Long = 5
Private Const COL_CONTRIBUTOR As Long = 2

Private Const ROW_FILE_BUILD As Long = 6
Private Const COL_FILE_BUILD As Long = 3

Private Const TABLE_START_ROW As Long = 9
Private Const TABLE_END_ROW As Long = 200

Private Const DEFAULT_LABEL_SHEET As String = "Default Labels"
Private Const ROW_DEFAULT_LABEL_LED_ON As Long = 2
Private Const COL_DEFAULT_LABEL_LED_ON As Long = 2
Private Const ROW_DEFAULT_LABEL_LED_OFF As Long = 3
Private Const COL_DEFAULT_LABEL_LED_OFF As Long = 2

' data table definitions
Private Const COL_PINNO As Long = 1
Private Const COL_PORTNO As Long = 2
Private Const COL_PGxNO As Long = 3
Private Const COL_RPxNO As Long = 4
Private Const COL_USER_LABEL As Long = 5
Private Const COL_COREASIGN As Long = 6
Private Const COL_ANx_ASIGN As Long = 7
Private Const COL_ADCORE_ASIGN As Long = 8
Private Const COL_ACMP_ASIGN As Long = 9
Private Const COL_PWM_ASIGN As Long = 10
Private Const COL_SF_ASIGN As Long = 11
Private Const COL_CORE_ID As Long = 12

'variables
Private CONTRIBUTOR As String
Private BOARD_LABEL As String
Private BOARD_NAME As String
Private PINMAP_VERSION As String
Private FILE_BUILD As String
Private GUARD_CONDITION_LABEL As String
Private CORE_TYPE As String

' This function will load the current user name into the Excel sheet
Public Function USERNAME()
    USERNAME = Environ$("UserName")
End Function

' This mcro will be called by the Excel sheet command button to generate the header file code
Public Sub CreateHeader()

On Error GoTo ErrSub

Dim i As Integer, dum As Variant
Dim core, core_start, core_stop As Integer
Dim strOutput, strOut As String

    ' initialize global label variables
    CORE_TYPE = Cells(ROW_CORE_TYPE, COL_CORE_TYPE)
    CONTRIBUTOR = Cells(ROW_CONTRIBUTOR, COL_CONTRIBUTOR)
    PINMAP_VERSION = "R" & Cells(ROW_VERSION, COL_VERSION)
    BOARD_NAME = Cells(ROW_BOARD_NAME, COL_BOARD_NAME)
    BOARD_LABEL = Cells(ROW_BOARD_NAME, COL_BOARD_NAME) & "_" & PINMAP_VERSION
    GUARD_CONDITION_LABEL = "__" & BOARD_NAME & "_" & PINMAP_VERSION & "_PINMAP_H__"
    FILE_BUILD = Format(Cells(ROW_FILE_BUILD, COL_FILE_BUILD), "#0000")

    ' add license and file header comment
    strOutput = GetInitialComment()
    
    ' add generic defines for port pin configuration
    strOutput = strOutput & "// Generated Content: Generic defines used to map device pins to board signals" & vbCrLf
    strOutput = strOutput & _
                "#ifndef PINDIR_INPUT" & vbCrLf & _
                "    #define PINDIR_INPUT 1" & vbCrLf & _
                "#endif" & vbCrLf & _
                "#ifndef PINDIR_OUTPUT" & vbCrLf & _
                "    #define PINDIR_OUTPUT 0" & vbCrLf & _
                "#endif" & vbCrLf & _
                vbCrLf & _
                "#ifndef PINSTATE_HIGH" & vbCrLf & _
                "    #define PINSTATE_HIGH 1" & vbCrLf & _
                "#endif" & vbCrLf & _
                "#ifndef PINSTATE_LOW" & vbCrLf & _
                "    #define PINSTATE_LOW 0" & vbCrLf & _
                "#endif" & vbCrLf & _
                vbCrLf & _
                "#ifndef PINCFG_OPEN_DRAIN" & vbCrLf & _
                "    #define PINCFG_OPEN_DRAIN 1" & vbCrLf & _
                "#endif" & vbCrLf & _
                "#ifndef PINCFG_PUSH_PULL" & vbCrLf & _
                "    #define PINCFG_PUSH_PULL 0" & vbCrLf & _
                "#endif" & vbCrLf & _
                vbCrLf

    ' add generic defines for LED indication configuration
    strOutput = strOutput & _
                "#ifndef LED_ON" & vbCrLf & _
                "    #define LED_ON " & Sheets(DEFAULT_LABEL_SHEET).Cells(ROW_DEFAULT_LABEL_LED_ON, COL_DEFAULT_LABEL_LED_ON) & vbCrLf & _
                "#endif" & vbCrLf & _
                "#ifndef LED_OFF" & vbCrLf & _
                "    #define LED_OFF " & Sheets("Default Labels").Cells(ROW_DEFAULT_LABEL_LED_OFF, COL_DEFAULT_LABEL_LED_OFF) & vbCrLf & _
                "#endif" & vbCrLf & _
                vbCrLf
    
    ' Separate declarations into CPU core sections
    If CORE_TYPE = "DUAL CORE" Then
        core_start = 1
        core_stop = 2
    ElseIf CORE_TYPE = "SINGLE CORE" Then
        core_start = 0
        core_stop = 0
    Else
        MsgBox "Please select a valid CPU/MCU Core Type." & vbTab, vbExclamation, "CodeGen.CreateHeader"
        Cells(ROW_CORE_TYPE, COL_CORE_TYPE).Select
        GoTo ExitSub
    End If
    
    For core = core_start To core_stop
    
        Select Case core
        Case 0:
            'single core devices don't need compile switches
        Case 1:
            strOutput = strOutput & "#if defined (__P33SMPS_CH_MSTR__)" & vbCrLf & vbCrLf
        Case 2:
            strOutput = strOutput & "#elif defined (__P33SMPS_CH_SLV1__)" & vbCrLf & vbCrLf
        End Select
    
        ' Loop through all pins
        For i = TABLE_START_ROW To TABLE_END_ROW
            
            If CInt(Cells(i, COL_CORE_ID)) = core Or core = 0 Then
            
                If Len(Trim(Cells(i, COL_PINNO))) = 0 And Len(Trim(Cells(i, COL_PORTNO))) = 0 Then Exit For
                
                    strOut = GetPinDeclarations(i)
                    
                    If core > 0 Then
                        strOut = Replace(strOut, vbCrLf, vbCrLf & vbTab, 1, -1, vbTextCompare)
                    End If
                    
                    If strOut = "CANCEL_CODE_GEN" Then
                        GoTo ExitSub
                    End If
                    
                    If (Len(strOut) > 0) Then
                        strOutput = strOutput & strOut & vbCrLf
                        'Debug.Print strOut & vbCrLf
                    End If
            
            End If
        
        Next i
    
    Next core

    ' finalize generated content
    If CORE_TYPE = "DUAL CORE" Then
        strOutput = strOutput & vbCrLf & vbCrLf & "#endif" & vbCrLf
    End If
    
    ' close guard condition
    strOutput = strOutput & vbCrLf & vbCrLf & "#endif" & vbTab & "/* " & GUARD_CONDITION_LABEL & " */" & vbCrLf
    
    ' Loading generated contents into output window
    frmOutput.txtOutput.Text = strOutput
    frmOutput.txtOutput.SelStart = 1
    
    If frmOutput.Visible = False Then
        frmOutput.Show
    End If

    ' update file version
    ActiveSheet.Unprotect
    dum = CInt(Cells(ROW_FILE_BUILD, COL_FILE_BUILD))
    Cells(ROW_FILE_BUILD, COL_FILE_BUILD) = dum + 1
    ActiveSheet.Protect DrawingObjects:=False, Contents:=True, Scenarios:= _
        False, AllowSorting:=True, AllowFiltering:=True, AllowUsingPivotTables:=False
        
    On Error Resume Next
    Cells(ROW_CORE_TYPE, COL_CORE_TYPE).Select
        
ExitSub:
    Exit Sub

ErrSub:
    MsgBox "Error " & Err.Number & ": " & vbCrLf & _
        Err.Description & vbTab, vbExclamation
        
    Resume Next

End Sub

Private Function GetInitialComment() As String
On Error GoTo ErrFun

Dim ans As Variant
Dim strOut As String
Dim strGuardCondition As String
Dim strBoardLabel As String

    ' add license
    
    ' add file header comment
    strOut = FILE_COMMENT_START & _
             FILE_COMMENT_DESCRIPTION & _
             FILE_COMMENT_NOTE & _
             FILE_COMMENT_EXAMPLE_A & _
             FILE_COMMENT_EXAMPLE_B & _
             FILE_COMMENT_END
    
    strOut = Replace(strOut, "%USERNAME%", CONTRIBUTOR, 1, -1, vbTextCompare)
    strOut = Replace(strOut, "%BOARD_NAME%", BOARD_NAME, 1, -1, vbTextCompare)
    strOut = Replace(strOut, "%BOARD_LABEL%", BOARD_LABEL, 1, -1, vbTextCompare)
    strOut = Replace(strOut, "%DATE%", Format(Now, "mm/dd/yyyy"), 1, -1, vbTextCompare)
    strOut = Replace(strOut, "%FILE_BUILD%", FILE_BUILD, 1, -1, vbTextCompare)
    
    ' add guard condition
    strGuardCondition = "__" & Cells(ROW_BOARD_NAME, COL_BOARD_NAME) & "_R" & Cells(ROW_VERSION, COL_VERSION) & "_PINMAP_H__"
    strOut = strOut & GUARD_CONDITION & _
                "#ifndef " & strGuardCondition & vbCrLf & _
                "#define " & strGuardCondition & vbCrLf & _
                vbCrLf

    ' add #include files
    strOut = strOut & Replace(FILE_INCLUSIONS, "%MCAL_INCLUDE_PATH%", Chr$(34) & MCAL_INCLUDE_PATH & Chr$(34), 1, -1, vbTextCompare)

    ' add pin-mapping file version
    strOut = strOut & PINMAP_VERSION_COMMENT
    strOut = strOut & "#define PINMAP_VERSION  " & Chr$(34) & "R" & Cells(ROW_VERSION, COL_VERSION) & Chr$(34) & vbCrLf
    strOut = strOut & COMMENT_SEPARATOR & vbCrLf

ExitFun:
    GetInitialComment = strOut
    Exit Function

ErrFun:
    ans = MsgBox("Error " & Err.Number & ": " & vbCrLf & Err.Description & vbTab & vbCrLf & _
                  vbCrLf & "Would you like to continue?", vbExclamation + vbYesNo)
    If ans = vbYes Then
        Resume Next
    Else
        strOut = "CODE GENERATION INCOMPLETE"
        GoTo ExitFun
    End If


End Function

Private Function GetPinDeclarations(SheetRow As Integer) As String
On Error GoTo ErrFun

Dim ans As Variant
Dim pnum, adin, adcore, is_shared_adc As Integer
Dim port, pwm_channel, pwm_pin As String
Dim strOut, dum, ref, pin As String

    port = Right$(Left$(Trim$(Cells(SheetRow, COL_PORTNO)), 2), 1) ' GetPortIndex(Cells(i, COL_PORTNO))
    strOut = ""     ' Clear buffer variable
    
    strOut = "// Device Pin #" & Trim(Cells(SheetRow, COL_PINNO)) & " is " & Trim(Cells(SheetRow, COL_PORTNO)) & vbCrLf
    
    If (Left(Trim(Cells(SheetRow, COL_PORTNO)), 1) = "R") Then
    
        'Create header declaration only for pins which are valid GPIOs
        
        pnum = Right$(Trim$(Cells(SheetRow, COL_PORTNO)), Len(Cells(SheetRow, COL_PORTNO)) - 2)  ' GetPinNum(Cells(i, COL_PORTNO))
        pin = UCase$(Trim(Cells(SheetRow, COL_PORTNO))) 'GetPortID(Cells(i, COL_PORTNO))
        ref = UCase$(Trim(Cells(SheetRow, COL_USER_LABEL)))
        If Len(Trim(ref)) = 0 Then
            ref = "DP" & Format(Trim$(Cells(SheetRow, COL_PINNO)), "00")
        End If
        
        strOut = strOut & "#define " & ref & "_TRIS    TRIS" & port & "bits.TRIS" & port & CStr(pnum) & " // GPIO direction register bit" & vbCrLf
        strOut = strOut & "#define " & ref & "_WR      LAT" & port & "bits.LAT" & port & CStr(pnum) & " // GPIO port latch register bit" & vbCrLf
        strOut = strOut & "#define " & ref & "_RD      PORT" & port & "bits.R" & port & CStr(pnum) & " // GPIO port register bit" & vbCrLf
        
        strOut = strOut & "#define " & ref & "_ODC     ODC" & port & "bits.ODC" & port & CStr(pnum) & " // GPIO port open drain configuration register bit" & vbCrLf
        strOut = strOut & "#define " & ref & "_CNPU    CNPU" & port & "bits.CNPU" & port & CStr(pnum) & " // GPIO port pull-up resistor register bit" & vbCrLf
        strOut = strOut & "#define " & ref & "_CNPD    CNPD" & port & "bits.CNPD" & port & CStr(pnum) & " // GPIO port pull-down resistor register bit" & vbCrLf
        
        strOut = strOut & "#define " & ref & "_CNEN0   CNEN0" & port & "bits.CNEN0" & port & CStr(pnum) & " // GPIO port change notification Enable register bit" & vbCrLf
        strOut = strOut & "#define " & ref & "_CNSTAT  CNSTAT" & port & "bits.CNSTAT" & port & CStr(pnum) & " // GPIO port change notification Status register bit" & vbCrLf
        strOut = strOut & "#define " & ref & "_CNEN1   CNEN1" & port & "bits.CNEN1" & port & CStr(pnum) & " // GPIO port change notification Edge Select Enable register bit" & vbCrLf
        strOut = strOut & "#define " & ref & "_CNF     CNF" & port & "bits.CNF" & port & CStr(pnum) & " // GPIO port change notification flag bit register bit" & vbCrLf
        
        If Len(Trim(Cells(SheetRow, COL_RPxNO))) > 0 Then
            strOut = strOut & "#define " & ref & "_RP      " & Right(Trim(Cells(SheetRow, COL_RPxNO)), Len(Trim(Cells(SheetRow, COL_RPxNO))) - 2) & " // Number of Remappable Pin" & vbCrLf
        End If

        strOut = strOut & "#define " & ref & "_SET     { asm volatile (" & Chr$(34) & "bset _LAT" & port & ", #" & pnum & " \n" & Chr$(34) & "); }" & vbCrLf
        strOut = strOut & "#define " & ref & "_CLEAR   { asm volatile (" & Chr$(34) & "bclr _LAT" & port & ", #" & pnum & " \n" & Chr$(34) & "); }" & vbCrLf
        strOut = strOut & "#define " & ref & "_TOGGLE  { asm volatile (" & Chr$(34) & "btg  _LAT" & port & ", #" & pnum & " \n" & Chr$(34) & "); }" & vbCrLf
            
        strOut = strOut & "#define " & ref & "_IS_ANALOG_INPUT  " & CStr(Abs(CInt(Len(Trim(Cells(SheetRow, COL_ANx_ASIGN))) > 0))) & " // Pin is/is not analog input " & vbCrLf
            
        ' add analog input declarations when available
        If (Len(Trim(Cells(SheetRow, COL_ANx_ASIGN))) > 0) Then
        
            If Left(Trim$(Cells(SheetRow, COL_ANx_ASIGN)), 2) = "AN" Then
                adin = Right$(Trim$(Cells(SheetRow, COL_ANx_ASIGN)), Len(Cells(SheetRow, COL_ANx_ASIGN)) - 2)
            ElseIf Left(Trim$(Cells(SheetRow, COL_ANx_ASIGN)), 4) = "S1AN" Then
                adin = Right$(Trim$(Cells(SheetRow, COL_ANx_ASIGN)), Len(Cells(SheetRow, COL_ANx_ASIGN)) - 4)
            Else
                MsgBox "Format of analog input name does not match template." & vbTab, vbCritical
                GoTo ExitFun
            End If
            
            adcore = Left$(Trim$(Cells(SheetRow, COL_ADCORE_ASIGN)), 1)
            is_shared_adc = CStr(Abs(CInt(InStr(1, Trim$(Cells(SheetRow, COL_ADCORE_ASIGN)), "shared", vbTextCompare) > 0)))
        
            strOut = strOut & "#define " & ref & "_ANSEL   _ANSEL" & port & CStr(pnum) & " // analog/digital pin configuration register bit" & vbCrLf
            strOut = strOut & "#define " & ref & "_ADCCORE " & adcore & " // index starts from zero, last index indicated shared adC core" & vbCrLf
                
            If is_shared_adc = 1 Then
                strOut = strOut & "#define " & ref & "_IS_SHARED_CORE true // AN input is routed to a dedicated or shared ACD core" & vbCrLf
            Else
                strOut = strOut & "#define " & ref & "_IS_SHARED_CORE false // AN input is routed to a dedicated or shared ACD core" & vbCrLf
            End If

            strOut = strOut & "#define " & ref & "_ADC_AN_INPUT " & adin & "   // ANx input pin number" & vbCrLf
            strOut = strOut & "#define " & ref & "_ADCBUF  ADCBUF" & adin & " // ADC buffer register for this input" & vbCrLf
            
            If adin < 16 Then
                strOut = strOut & "#define " & ref & "_ADC_ANIE ADIELbits.IE" & adin & vbCrLf
                strOut = strOut & "#define " & ref & "_ADC_ANEIE ADEIELbits.EIEN" & adin & vbCrLf
            Else
                strOut = strOut & "#define " & ref & "_ADC_ANIE ADIEHbits.IE" & adin & vbCrLf
                strOut = strOut & "#define " & ref & "_ADC_ANEIE ADEIEHbits.EIEN" & adin & vbCrLf
            End If
            
            strOut = strOut & "#define " & ref & "_ADC_IF   _ADCAN" & adin & "IF // interrupt flag bit" & vbCrLf
            strOut = strOut & "#define " & ref & "_ADC_IE   _ADCAN" & adin & "IE // interrupt enable bit" & vbCrLf
            strOut = strOut & "#define " & ref & "_ADC_IP   _ADCAN" & adin & "IP // interrupt priority for this analog input" & vbCrLf
            strOut = strOut & "#define " & ref & "_ADC_RDY  _AN" & adin & "RDY // ADC buffer ready bit" & vbCrLf
            strOut = strOut & "#define _" & ref & "_ADC_Interrupt _ADCAN" & adin & "Interrupt" & vbCrLf
        
            strOut = strOut & "#define " & ref & "_INIT_ANALOG" & vbTab & "{" & ref & "_ANSEL = 1; " & ref & "_WR = PINSTATE_HIGH; " & ref & "_TRIS = PINDIR_INPUT;} // initialization macro for analog input" & vbCrLf
        
        End If
        
        strOut = strOut & "#define " & ref & "_INIT_OUTPUT  {" & ref & "_WR = PINSTATE_LOW; " & ref & "_TRIS = PINDIR_OUTPUT;} // initialization macro for digital output" & vbCrLf
        strOut = strOut & "#define " & ref & "_INIT_INPUT   {" & ref & "_WR = PINSTATE_HIGH; " & ref & "_TRIS = PINDIR_INPUT;} // initialization macro for digital input" & vbCrLf
    
    
        'add additional declarations for PWM pins if available
        If (Len(Trim(Cells(SheetRow, COL_PWM_ASIGN))) >= 5) Then '(PWM labels are at least 5 characters long)
        
            If Left(Trim$(Cells(SheetRow, COL_PWM_ASIGN)), 1) = "S" Then
            'slave core declaration
                dum = Right$(Trim$(Cells(SheetRow, COL_PWM_ASIGN)), Len(Cells(SheetRow, COL_PWM_ASIGN)) - 5)
            ElseIf Left(Trim$(Cells(SheetRow, COL_PWM_ASIGN)), 3) = "PWM" Then
            'master/single core declaration
                dum = Right$(Trim$(Cells(SheetRow, COL_PWM_ASIGN)), Len(Cells(SheetRow, COL_PWM_ASIGN)) - 3)
            Else
                MsgBox "Format of PWM output name does not match template." & vbTab, vbCritical
                GoTo ExitFun
            End If
            
            pwm_channel = Left$(Trim$(dum), Len(dum) - 1) ' extracts the PWM channel number 1...n
            pwm_pin = UCase(Right$(Trim$(dum), 1)) ' extracts L or H
            
            strOut = strOut & "#define " & ref & "_PGx_CHANNEL  " & pwm_channel & " // PWM channel index" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGx_PER      PG" & pwm_channel & "PER // PWM channel period register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGx_PHASE    PG" & pwm_channel & "PHASE // PWM channel phase register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGx_DC       PG" & pwm_channel & "DC // PWM channel duty cycle register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGx_DCA      PG" & pwm_channel & "DCA// PWM channel duty cycle A register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGx_DTH      PG" & pwm_channel & "DTH // PWM channel rising edge dead time register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGx_DTL      PG" & pwm_channel & "DTL // PWM channel falling edge dead time register" & vbCrLf
            
            If InStr(1, pwm_pin, "H", vbTextCompare) = 1 Then
                strOut = strOut & "#define " & ref & "_PGx_OVRENH   PG" & pwm_channel & "IOCONLbits.OVRENH // PWM channel IO config register override high control bit" & vbCrLf
                strOut = strOut & "#define " & ref & "_PGx_PENH     PG" & pwm_channel & "IOCONLbits.PENH // PWM channel IO config register pin enable high control bit" & vbCrLf
            ElseIf InStr(1, pwm_pin, "L", vbTextCompare) = 1 Then
                strOut = strOut & "#define " & ref & "_PGx_OVRENL   PG" & pwm_channel & "IOCONLbits.OVRENL // PWM channel IO config register override low control bit" & vbCrLf
                strOut = strOut & "#define " & ref & "_PGx_PENL     PG" & pwm_channel & "IOCONLbits.PENL // PWM channel IO config register pin enable low control bit" & vbCrLf
            End If
        
            strOut = strOut & "#define " & ref & "_PGxUPDREQ    PG" & pwm_channel & "STATbits.UPDREQ // PWM channel ADC trigger A register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGxTRIGA     PG" & pwm_channel & "TRIGA // PWM channel ADC trigger A register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGxTRIGB     PG" & pwm_channel & "TRIGB // PWM channel ADC trigger A register" & vbCrLf
            strOut = strOut & "#define " & ref & "_PGxTRIGC     PG" & pwm_channel & "TRIGC // PWM channel ADC trigger A register" & vbCrLf
        
            If pwm_pin = "H" Then
        
                strOut = strOut & "#define " & ref & "_PWM_IF       _PWM" & pwm_channel & "IF // interrupt flag bit" & vbCrLf
                strOut = strOut & "#define " & ref & "_PWM_IE       _PWM" & pwm_channel & "IE // interrupt enable bit" & vbCrLf
                strOut = strOut & "#define " & ref & "_PWM_IP       _PWM" & pwm_channel & "IP // interrupt priority for this analog input" & vbCrLf
                strOut = strOut & "#define _" & ref & "_PWM_Interrupt _PWM" & pwm_channel & "Interrupt // Interrupt Service Routine name declaration" & vbCrLf
            
            End If
            
        
        
        End If
            
    Else
    ' Function pins like VDD, VSS or MCLR are bypassed
        Debug.Print "Row " & CStr(SheetRow) & ": Device Pin #" & Trim(Cells(SheetRow, COL_PINNO)) & " is " & Trim(Cells(SheetRow, COL_PORTNO))
        
    End If


ExitFun:
    GetPinDeclarations = strOut
    Exit Function

ErrFun:
    ans = MsgBox("Error " & Err.Number & ": " & vbCrLf & Err.Description & vbTab & vbCrLf & _
                  vbCrLf & "Would you like to continue?", vbExclamation + vbYesNo)
    If ans = vbYes Then
        Resume Next
    Else
        strOut = "CANCEL_CODE_GEN"
        GoTo ExitFun
    End If

End Function

Private Function GetPortIndex(portID As String) As String

Dim dum As String
    
    dum = Right$(Left$(Trim$(portID), 2), 1)
    GetPortIndex = dum

End Function

Private Function GetPinNum(portID As String) As Integer

Dim dum As String
    
    dum = Right$(Trim$(portID), Len(portID) - 2)
    GetPinNum = CInt(dum)

End Function

Private Function GetPortID(portID As String) As String

Dim dum As String
    
    dum = UCase$(Trim(portID))
    GetPortID = dum

End Function


