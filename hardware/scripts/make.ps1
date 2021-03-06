param(
[Parameter(ValueFromRemainingArguments=$true)]
$makeArgs = @()
)

$toolchainFolder = 'C:\CodeSourcery'

$base = [IO.Path]::GetDirectoryName($MyInvocation.MyCommand.Definition)

function Preserve-Path([ScriptBlock]$block)
{
    $oldPath = $env:Path

    Try
    {
        Invoke-Command -ScriptBlock $block
    }
    Finally
    {
        $env:Path = $oldPath
    }
}

Preserve-Path {
    $env:Path = "$($toolchainFolder)\toolchain\bin;$($toolchainFolder)\coreutils;c:\windows\system32"

   cs-make $makeArgs
}
