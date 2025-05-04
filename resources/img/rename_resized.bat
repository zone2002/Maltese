@echo off
setlocal EnableDelayedExpansion

REM ——————————————————————————————
REM 1. 列出当前目录下的所有子文件夹
REM ——————————————————————————————
echo 可用的文件夹列表：
set idx=0
for /d %%D in (*) do (
    set /a idx+=1
    echo    !idx!^) %%D
    set "folder[!idx!]=%%D"
)

if !idx! equ 0 (
    echo 当前目录下没有子文件夹可选。
    pause
    goto :eof
)

REM ——————————————————————————————
REM 2. 让用户选择目录序号
REM ——————————————————————————————
:ChooseFolder
set /p choice="请输入要处理的文件夹序号 (1-%idx%): "
REM 验证输入是否为数字且在有效范围内
for /f "delims=0123456789" %%A in ("%choice%") do (
    echo 无效输入，请输入数字。
    goto :ChooseFolder
)
if !choice! lss 1 (
    echo 序号太小，请重新输入。
    goto :ChooseFolder
)
if !choice! gtr !idx! (
    echo 序号太大，请重新输入。
    goto :ChooseFolder
)

set "targetDir=!folder[%choice%]!"
echo 已选择文件夹：!targetDir!
echo.

REM ——————————————————————————————
REM 3. 进入目标文件夹并逐一重命名 *_resized.png
REM ——————————————————————————————
pushd "!targetDir!" || (
    echo 无法切换到目录 !targetDir!。
    goto Cleanup
)

echo 正在处理目录：%CD%
set count=0

for %%F in (*_resized.png) do (
    set "oldName=%%F"
    REM 去掉后缀 _resized
    set "name=%%~nF"
    set "base=!name:_resized=!"
    set "newName=!base!.png"

    ren "%%F" "!newName!" 2>nul
    if exist "!newName!" (
        echo 成功: !oldName!  →  !newName!
        set /a count+=1
    ) else (
        echo 失败: !oldName!
    )
)

echo.
if !count! equ 0 (
    echo 未找到任何 *_resized.png 文件或全部重命名失败。
) else (
    echo 总共成功重命名 !count! 个文件。
)

popd

:Cleanup
pause
endlocal
