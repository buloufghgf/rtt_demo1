
::打开回显
@echo on

::删除文件
del=/s /a /f "JLinkLog.txt"
del=/s /a /f "*.ini"
del=/s /a /f "*.uvguix.*"
del=/s /a /f "*.scvd"

::删除 "DebugConfig" "Listings" "Objects"文件夹
for /f "delims=" %%i in ('dir /ad /b /s "DebugConfig" "Listings" "Obj" "Objects"') do (
   rd /s /q "%%i"
)

::删除空文件夹
::for /f "tokens=*" %%i in ('dir/s/b/ad^|sort /r') do rd "%%i"

exit