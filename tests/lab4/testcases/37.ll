; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/37.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define void @foo() {
label.entry:
  %0 = alloca i32
  store i32 10, i32* %0
  ret void
}
define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  call void @foo()
  %2 = load i32, i32* %1
  ret i32 %2
}
