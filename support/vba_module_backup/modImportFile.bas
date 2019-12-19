Attribute VB_Name = "modImportFile"
Option Explicit

Private Const TABLE_START_ROW As Long = 9
Private Const TABLE_END_ROW As Long = 200

Private Const COL_MSTR_SOURCE As Long = 23
Private Const COL_SLV1_SOURCE As Long = 24

Private Const COL_PINNO As Long = 1
Private Const COL_PORTNO As Long = 2
Private Const COL_PGxNO As Long = 3
Private Const COL_RPxNO As Long = 4
Private Const COL_USER_LABEL As Long = 5
Private Const COL_COREASIGN As Long = 6
Private Const COL_ANx_ASIGN As Long = 7 + COL_COREASIGN
Private Const COL_ADCORE_ASIGN As Long = 8 + COL_COREASIGN
Private Const COL_ACMP_ASIGN As Long = 9 + COL_COREASIGN
Private Const COL_PWM_ASIGN As Long = 10 + COL_COREASIGN
Private Const COL_SF_ASIGN As Long = 11 + COL_COREASIGN
'Private Const COL_CORE_ID As Long = 12 + COL_COREASIGN


Public Sub ParsePinFunctions()
On Error GoTo ErrSub

Dim i As Long, j As Long
Dim xdum As String
Dim cdum As Variant


    For i = TABLE_START_ROW To TABLE_END_ROW
    
        If Len(Trim(Cells(i, COL_MSTR_SOURCE))) = 0 Then Exit For
        
        'Delete row entries
        Cells(i, COL_PORTNO) = ""
        Cells(i, COL_PGxNO) = ""
        Cells(i, COL_RPxNO) = ""
'        Cells(i, COL_USER_LABEL) = ""      ' do not delete user label
        If Cells(2, 2) = "SINGLE CORE" Then
            Cells(i, COL_COREASIGN) = "MSTR"
        ElseIf Cells(2, 2) = "DUAL CORE" Then
            Cells(i, COL_COREASIGN) = "MSTR"
        End If
        Cells(i, COL_ANx_ASIGN) = ""
        Cells(i, COL_ADCORE_ASIGN) = ""
        Cells(i, COL_ACMP_ASIGN) = ""
        Cells(i, COL_PWM_ASIGN) = ""
        Cells(i, COL_SF_ASIGN) = ""
        
        cdum = Cells(i, COL_MSTR_SOURCE)
        cdum = Split(cdum, "/", -1, vbTextCompare)
        
        Cells(i, COL_PORTNO) = CStr(cdum(UBound(cdum)))
        
        If UBound(cdum) > 0 Then
            
            For j = LBound(cdum) To UBound(cdum) - 1
            
                xdum = CStr(cdum(j))
                
                If InStr(1, xdum, "PWM", vbTextCompare) > 0 Then
                    Cells(i, COL_PWM_ASIGN) = xdum
                ElseIf _
                    InStr(1, xdum, "MCLR", vbTextCompare) > 0 Or _
                    InStr(1, xdum, "PGD", vbTextCompare) > 0 Or _
                    InStr(1, xdum, "PGC", vbTextCompare) > 0 _
                Then
                    Cells(i, COL_PGxNO) = xdum
                ElseIf InStr(1, xdum, "RP", vbTextCompare) > 0 Then
                    Cells(i, COL_RPxNO) = xdum
                ElseIf InStr(1, xdum, "AN", vbTextCompare) > 0 Then
                    Cells(i, COL_ANx_ASIGN) = xdum
                ElseIf InStr(1, xdum, "CMP", vbTextCompare) > 0 Then
                    Cells(i, COL_ACMP_ASIGN) = xdum
                Else
                    If Len(Cells(i, COL_SF_ASIGN)) > 0 Then
                        Cells(i, COL_SF_ASIGN) = Cells(i, COL_SF_ASIGN) & "/"
                    End If
                    Cells(i, COL_SF_ASIGN) = Cells(i, COL_SF_ASIGN) & xdum
                End If
                
            Next j
        
        Else
            
            xdum = CStr(cdum(UBound(cdum)))
            
            If InStr(1, xdum, "PWM", vbTextCompare) > 0 Then
                Cells(i, COL_PWM_ASIGN) = xdum
            ElseIf _
                InStr(1, xdum, "MCLR", vbTextCompare) > 0 Or _
                InStr(1, xdum, "PGD", vbTextCompare) > 0 Or _
                InStr(1, xdum, "PGC", vbTextCompare) > 0 _
            Then
                Cells(i, COL_PGxNO) = xdum
            ElseIf InStr(1, xdum, "RP", vbTextCompare) > 0 Then
                Cells(i, COL_RPxNO) = xdum
            ElseIf InStr(1, xdum, "AN", vbTextCompare) > 0 Then
                Cells(i, COL_ANx_ASIGN) = xdum
            ElseIf InStr(1, xdum, "CMP", vbTextCompare) > 0 Then
                Cells(i, COL_ACMP_ASIGN) = xdum
            Else
                If Len(Cells(i, COL_SF_ASIGN)) > 0 Then
                    Cells(i, COL_SF_ASIGN) = Cells(i, COL_SF_ASIGN) & "/"
                End If
                Cells(i, COL_SF_ASIGN) = Cells(i, COL_SF_ASIGN) & xdum
            End If

        End If

    Next i

    MsgBox "Parsing complete", vbInformation

ExitSub:
    Exit Sub

ErrSub:
    MsgBox "Parsing Error (" & Err.Number & "): " & vbCrLf & Err.Description & vbTab & vbCrLf & _
           "(Cell " & i & "-" & j & ")" & vbTab, _
           vbExclamation, "ParsePinFunctions"
    Resume ExitSub

End Sub
