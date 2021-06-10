; ModuleID = 'while.c'
source_filename = "while.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

define dso_local i32 @main() #0 {
entry:
    ;int a,i;
    %a = alloca i32, align 4
    %i = alloca i32, align 4
    ;a = 10; i = 0;
    store i32 10, i32* %a, align 4
    store i32 0, i32* %i, align 4
    br label %while.cond
while.cond:
    %i.value = load i32, i32* %i, align 4
    ;i < 10
    %cmp = icmp slt i32 %i.value, 10
    br i1 %cmp, label %while.body, label %while.end
while.body:
    ;i++
    %i.value1 = load i32, i32* %i, align 4
    %add = add nsw i32 %i.value1, 1
    store i32 %add, i32* %i, align 4
    ;a = a + i; 
    %a.value = load i32, i32* %a, align 4
    ;Note that 'add' is the newest value of i
    %add1 = add nsw i32 %a.value, %add
    store i32 %add1, i32* %a, align 4
    br label %while.cond
while.end:
    %a.value1 = load i32, i32* %a, align 4
    ret i32 %a.value1
}