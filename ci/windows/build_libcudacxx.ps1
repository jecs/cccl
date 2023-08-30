
Param(
    [Alias("cxx")]
    [int]$CXX_STANDARD = 17,
    [Alias("archs")]
    [string]$GPU_ARCHS = "70"
)

$CURRENT_PATH = Split-Path $pwd -leaf
If($CURRENT_PATH -ne "ci") {
    Write-Host "Moving to ci folder"
    pushd "$PSScriptRoot/.."
}

Remove-Module -Name build_common
Import-Module $PSScriptRoot/build_common.psm1 -ArgumentList $CXX_STANDARD, $GPU_ARCHS

$CMAKE_OPTIONS = @(
    "-DCCCL_ENABLE_THRUST=OFF"
    "-DCCCL_ENABLE_LIBCUDACXX=ON"
    "-DCCCL_ENABLE_CUB=OFF"
    "-DCCCL_ENABLE_TESTING=OFF"
    "-DLIBCUDACXX_ENABLE_LIBCUDACXX_TESTS=ON"
)

$LIT_OPTIONS = @(
    "-v"
    "--no-progress-bar"
    "-Dexecutor=""NoopExecutor()"""
    "-Dcompute_archs=$GPU_ARCHS"
    "-Dstd=c++$CXX_STANDARD"
    "$BUILD_DIR/libcudacxx/test"
)

configure $CMAKE_OPTIONS

sccache_stats('Start')
Start-Process lit -Wait -NoNewWindow -ArgumentList $LIT_OPTIONS
sccache_stats('Stop')

If($CURRENT_PATH -ne "ci") {
    popd
}
