; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/16.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @test(i32 %0) {
label.entry:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = alloca i32
  %3 = load i32, i32* %1
  ret i32 %3
}
define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca float
  %2 = alloca i32
  store float 0x4004000000000000, float* %1
  %3 = load float, float* %1
  %4 = fptosi float %3 to i32
  %5 = call i32 @test(i32 %4)
  store i32 %5, i32* %2
  %6 = load i32, i32* %2
  ret i32 %6
}
