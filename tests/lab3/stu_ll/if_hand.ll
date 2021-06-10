source_filename = "if.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define dso_local i32 @main() #0 {
entry:
    %a = alloca float, align 4
    store float 0x40163851E0000000, float* %a, align 4
    %a.value = load float, float* %a, align 4
    %cmp = fcmp ogt float %a.value, 1.000000e+00
    br i1 %cmp, label %if.then, label %if.end
if.then:
    %0 = alloca i32, align 4
    store i32 233, i32* %0, align 4
    %1 = load i32, i32* %0, align 4
    ret i32 %1
if.end:
    %2 = alloca i32, align 4
    store i32 0, i32* %2, align 4
    %3 = load i32, i32* %2, align 4
    ret i32 %3
}