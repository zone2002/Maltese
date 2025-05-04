@echo off
cls
setlocal EnableDelayedExpansion

:: —— 第一步：列出所有子文件夹并编号
set /a count=0
echo 可选文件夹：
for /d %%D in (*) do (
    set /a count+=1
    echo    !count! - %%D
    set "dir!count!=%%D"
)
echo.

:: —— 第二步：用户输入编号，选择目标文件夹
set /p choice=请输入要处理的文件夹编号 (1-%count%):
if not defined dir%choice% (
    echo 无效编号，程序退出。
    goto :eof
)
set "target=!dir%choice%!"
echo 您选择的文件夹： %target%
echo.

:: —— 第三步：进入目标文件夹并重命名（仅处理 .png 文件）
pushd "%target%"
for %%F in (*.*) do (
    rem 获取文件扩展名（包括点号），并转换为小写
    set "ext=%%~xF"
    set "ext=!ext:~1!"
    for /f "delims=" %%G in ("!ext!") do set "ext=%%~G"
    if /I "!ext!"=="png" (
        rem 取出文件名数字部分
        set "fname=%%~nF"
        rem 计算 newnum = 原数字 - 1
        set /a newnum=!fname! - 1
        ren "%%F" "%target%_!newnum!%%~xF"
        echo 重命名 "%%F" 为 "%target%_!newnum!%%~xF"
    ) else (
        echo 跳过非 PNG 文件： %%F
    )
)
popd

echo.
echo 所有 .png 文件处理完毕！
pause
