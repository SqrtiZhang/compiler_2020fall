; ModuleID = 'assign.c'
source_filename = "assign.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define dso_local i32 @main() #0 {
entry:
    %a = alloca [10 x i32], align 16
    ;a[0] index
    %a0 = getelementptr inbounds [10 x i32], [10 x i32]* %a, i64 0, i64 0
    ;a[0] = 10
    store i32 10, i32* %a0, align 4
    %0 = load i32, i32* %a0, align 4
    %mul = mul nsw i32 %0, 2
    ;a[1] index
    %a1 = getelementptr inbounds [10 x i32], [10 x i32]* %a, i64 0, i64 1
    ;a[1] = mul = %0 * 2 = a[0] * 2
    store i32 %mul, i32* %a1, align 4
    %1 = load i32, i32* %a1, align 4
    ;return 
    ret i32 %1
}

