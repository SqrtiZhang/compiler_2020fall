; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/30.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  store i32 1, i32* %1
  %2 = load i32, i32* %1
  %3 = icmp sgt i32 %2, 1
  %4 = zext i1 %3 to i32
  ret i32 %4
}
