# JapaneseWinClipboardUnicodeProblem
VS MFC solution to demonstrate that extended ASCII chars copied to the clipboard or displayed in a COM object using OLE on Japanese version of Windows are not rendered properly.
Problem statement: I have a (Visual Studio) MFC Unicode app that is used by some people in Japan. One of the app's functions outputs an enhanced metafile to the clipboard for pasting into other applications. The MFC app is an OLE server app and uses COleServerItem::CopyToClipboard to add the metafile to the clipboard. Some of the text in the metafile use glyphs with character codes > 127. On a Japanese version of Windows, those glyphs do not render properly when pasted into another application. Instead of the expected symbols, they are rendered as some latin chars in some other font. Doesn't make any difference what font is used (unless it happens to be whatever the fallback font is in which case it's a don't care.) If I change the strings that use the glyphs from CString(wchar_t) to CStringA (char), and use TextOutA instead of the Unicode verison, then the glyphs do render properly! So much for Unicode.
An additional workaround, instead of using COleServerItem::CopyToClipboard, is to "manually" put data on the clipboard using standard C++ clipboard functions like OpenClipboard, EmptyClipboard, SetClipboardData, CloseClipboard. This also fixes the problem without having to change the strings in the metafile to ASCII!! So one might think that the problem is in COleServerItem::CopyToClipboard.
However, there is a related problem that doesn't involve the clipboard. The app uses a legacy MSFlexGrid OCX. The com object uses OLE which is Unicode, but on a Japanes Windows system, when the grids are displayed on screen, the special glyphs (extended ascii char codes > 127) also render improperly.
I have created a Git repository (this one) with a Visual Studio MFC solution that demonstrates the problem.
To use the demo:
1.	Build the solution.
2.	Copy the .exe to a Japanese verison of Windows.
3.	Run the program to display the output.
4.	Use Edit->Copy or ctrl-c to copy the output to the clipboard as an enhanced metafile.
5.	Paste into WordPad (or Word if installed) and verify that the "extended" characters from the Symbol font are rendered improperly in some other (fallback) font.
6.	Alternatively, edit the code and… 
