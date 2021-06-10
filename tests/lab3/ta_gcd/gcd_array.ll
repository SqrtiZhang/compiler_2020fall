; ModuleID = 'gcd_array.c'
source_filename = "gcd_array.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@x = common dso_local global [1 x i32] zeroinitializer, align 4
@y = common dso_local global [1 x i32] zeroinitializer, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @gcd(i32 %u, i32 %v) #0 {
entry:
  %retval = alloca i32, align 4
  %u.addr = alloca i32, align 4
  %v.addr = alloca i32, align 4
  store i32 %u, i32* %u.addr, align 4
  store i32 %v, i32* %v.addr, align 4
  %0 = load i32, i32* %v.addr, align 4
  %cmp = icmp eq i32 %0, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %u.addr, align 4
  store i32 %1, i32* %retval, align 4
  br label %return

if.else:                                          ; preds = %entry
  %2 = load i32, i32* %v.addr, align 4
  %3 = load i32, i32* %u.addr, align 4
  %4 = load i32, i32* %u.addr, align 4
  %5 = load i32, i32* %v.addr, align 4
  %div = sdiv i32 %4, %5
  %6 = load i32, i32* %v.addr, align 4
  %mul = mul nsw i32 %div, %6
  %sub = sub nsw i32 %3, %mul
  %call = call i32 @gcd(i32 %2, i32 %sub)
  store i32 %call, i32* %retval, align 4
  br label %return

return:                                           ; preds = %if.else, %if.then
  %7 = load i32, i32* %retval, align 4
  ret i32 %7
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @funArray(i32* %u, i32* %v) #0 {
entry:
  %u.addr = alloca i32*, align 8
  %v.addr = alloca i32*, align 8
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %temp = alloca i32, align 4
  store i32* %u, i32** %u.addr, align 8
  store i32* %v, i32** %v.addr, align 8
  %0 = load i32*, i32** %u.addr, align 8
  %arrayidx = getelementptr inbounds i32, i32* %0, i64 0
  %1 = load i32, i32* %arrayidx, align 4
  store i32 %1, i32* %a, align 4
  %2 = load i32*, i32** %v.addr, align 8
  %arrayidx1 = getelementptr inbounds i32, i32* %2, i64 0
  %3 = load i32, i32* %arrayidx1, align 4
  store i32 %3, i32* %b, align 4
  %4 = load i32, i32* %a, align 4
  %5 = load i32, i32* %b, align 4
  %cmp = icmp slt i32 %4, %5
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %a, align 4
  store i32 %6, i32* %temp, align 4
  %7 = load i32, i32* %b, align 4
  store i32 %7, i32* %a, align 4
  %8 = load i32, i32* %temp, align 4
  store i32 %8, i32* %b, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %9 = load i32, i32* %a, align 4
  %10 = load i32, i32* %b, align 4
  %call = call i32 @gcd(i32 %9, i32 %10)
  ret i32 %call
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 90, i32* getelementptr inbounds ([1 x i32], [1 x i32]* @x, i64 0, i64 0), align 4
  store i32 18, i32* getelementptr inbounds ([1 x i32], [1 x i32]* @y, i64 0, i64 0), align 4
  %call = call i32 @funArray(i32* getelementptr inbounds ([1 x i32], [1 x i32]* @x, i64 0, i64 0), i32* getelementptr inbounds ([1 x i32], [1 x i32]* @y, i64 0, i64 0))
  ret i32 %call
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.1 "}
