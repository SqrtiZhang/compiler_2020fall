; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/36.cminus"

@a = global [6 x float] zeroinitializer
declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define void @foo() {
label.entry:
  %0 = alloca i32
  %1 = fptosi float 0x40239999a0000000 to i32
  store i32 %1, i32* %0
  %2 = getelementptr [6 x float], [6 x float]* @a, i32 0, i32 0
  %3 = load i32, i32* %0
  %4 = sitofp i32 %3 to float
  store float %4, float* %2
  ret void
}
define i32 @main() {
label.entry:
  %0 = alloca i32
  call void @foo()
  %1 = getelementptr [6 x float], [6 x float]* @a, i32 0, i32 0
  %2 = load float, float* %1
  %3 = fptosi float %2 to i32
  ret i32 %3
}
