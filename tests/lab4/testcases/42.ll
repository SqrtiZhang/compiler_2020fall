; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/42.cminus"

@x = global [10 x float] zeroinitializer
declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @minloc(float* %0, i32 %1, i32 %2) {
label.entry:
  %3 = alloca float*
  store float* %0, float** %3
  %4 = alloca i32
  store i32 %1, i32* %4
  %5 = alloca i32
  store i32 %2, i32* %5
  %6 = alloca i32
  %7 = alloca i32
  %8 = alloca float
  %9 = alloca i32
  %10 = load i32, i32* %4
  store i32 %10, i32* %9
  %11 = load i32, i32* %4
  %12 = load float*, float** %3
  %13 = getelementptr float, float* %12, i32 %11
  %14 = load float, float* %13
  store float %14, float* %8
  %15 = load i32, i32* %4
  %16 = add i32 %15, 1
  store i32 %16, i32* %7
  br label %label.cmp_bb1
label.cmp_bb1:
  %17 = load i32, i32* %7
  %18 = load i32, i32* %5
  %19 = icmp slt i32 %17, %18
  br i1 %19, label %label.while_body_bb1, label %label.end_bb1
label.while_body_bb1:
  %20 = load i32, i32* %7
  %21 = load float*, float** %3
  %22 = getelementptr float, float* %21, i32 %20
  %23 = load float, float* %22
  %24 = load float, float* %8
  %25 = fcmp ult float %23,%24
  br i1 %25, label %label.trueBB1, label %label.retBB1
label.end_bb1:
  %26 = load i32, i32* %9
  ret i32 %26
label.trueBB1:
  %27 = load i32, i32* %7
  %28 = load float*, float** %3
  %29 = getelementptr float, float* %28, i32 %27
  %30 = load float, float* %29
  store float %30, float* %8
  %31 = load i32, i32* %7
  store i32 %31, i32* %9
  br label %label.retBB1
label.falseBB1:
  br label %label.retBB1
label.retBB1:
  %32 = load i32, i32* %7
  %33 = add i32 %32, 1
  store i32 %33, i32* %7
  br label %label.cmp_bb1
}
define void @sort(float* %0, float %1, i32 %2) {
label.entry:
  %3 = alloca float*
  store float* %0, float** %3
  %4 = alloca float
  store float %1, float* %4
  %5 = alloca i32
  store i32 %2, i32* %5
  %6 = alloca i32
  %7 = alloca i32
  %8 = load float, float* %4
  %9 = fptosi float %8 to i32
  store i32 %9, i32* %6
  br label %label.cmp_bb1
label.cmp_bb1:
  %10 = load i32, i32* %6
  %11 = load i32, i32* %5
  %12 = sub i32 %11, 1
  %13 = icmp slt i32 %10, %12
  br i1 %13, label %label.while_body_bb1, label %label.end_bb1
label.while_body_bb1:
  %14 = alloca i32
  %15 = load float*, float** %3
  %16 = load i32, i32* %6
  %17 = load i32, i32* %5
  %18 = call i32 @minloc(float* %15, i32 %16, i32 %17)
  store i32 %18, i32* %7
  %19 = load i32, i32* %7
  %20 = load float*, float** %3
  %21 = getelementptr float, float* %20, i32 %19
  %22 = load float, float* %21
  %23 = fptosi float %22 to i32
  store i32 %23, i32* %14
  %24 = load i32, i32* %7
  %25 = load float*, float** %3
  %26 = getelementptr float, float* %25, i32 %24
  %27 = load i32, i32* %6
  %28 = load float*, float** %3
  %29 = getelementptr float, float* %28, i32 %27
  %30 = load float, float* %29
  store float %30, float* %26
  %31 = load i32, i32* %6
  %32 = load float*, float** %3
  %33 = getelementptr float, float* %32, i32 %31
  %34 = load i32, i32* %14
  %35 = sitofp i32 %34 to float
  store float %35, float* %33
  %36 = load i32, i32* %6
  %37 = add i32 %36, 1
  store i32 %37, i32* %6
  br label %label.cmp_bb1
label.end_bb1:
  ret void
}
define void @main() {
label.entry:
  %0 = alloca i32
  store i32 0, i32* %0
  br label %label.cmp_bb1
label.cmp_bb1:
  %1 = load i32, i32* %0
  %2 = icmp slt i32 %1, 10
  br i1 %2, label %label.while_body_bb1, label %label.end_bb1
label.while_body_bb1:
  %3 = load i32, i32* %0
  %4 = getelementptr [10 x float], [10 x float]* @x, i32 0, i32 %3
  %5 = call i32 @input()
  %6 = sitofp i32 %5 to float
  store float %6, float* %4
  %7 = load i32, i32* %0
  %8 = add i32 %7, 1
  store i32 %8, i32* %0
  br label %label.cmp_bb1
label.end_bb1:
  %9 = getelementptr [10 x float], [10 x float]* @x, i32 0, i32 0
  %10 = sitofp i32 0 to float
  call void @sort(float* %9, float %10, i32 10)
  store i32 0, i32* %0
  br label %label.cmp_bb2
label.cmp_bb2:
  %11 = load i32, i32* %0
  %12 = icmp slt i32 %11, 10
  br i1 %12, label %label.while_body_bb2, label %label.end_bb2
label.while_body_bb2:
  %13 = load i32, i32* %0
  %14 = getelementptr [10 x float], [10 x float]* @x, i32 0, i32 %13
  %15 = load float, float* %14
  %16 = fptosi float %15 to i32
  call void @output(i32 %16)
  %17 = load i32, i32* %0
  %18 = add i32 %17, 1
  store i32 %18, i32* %0
  br label %label.cmp_bb2
label.end_bb2:
  ret void
}
