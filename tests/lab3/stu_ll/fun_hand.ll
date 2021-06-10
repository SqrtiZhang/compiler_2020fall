; ModuleID = 'fun.c'
source_filename = "fun.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define dso_local i32 @callee(i32 %a) #0 {
entry:
    ;mul = 2 * a
    %mul = mul nsw i32 2, %a
    ret i32 %mul
}

define dso_local i32 @main() #0 {
entry:
    %call = call i32 @callee(i32 110)
    ret i32 %call
}
