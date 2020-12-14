; ModuleID = 'cminus'
source_filename = "../tests/lab4/testcases/28.cminus"

declare i32 @input()

declare void @output(i32)

declare void @outputFloat(float)

declare void @neg_idx_except()

define i32 @main() {
label.entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca i32
  store i32 1, i32* %1
  %3 = load i32, i32* %1
  %4 = icmp ne i32 %3, 0
  br i1 %4, label %label.trueBB1, label %label.retBB1
label.trueBB1:
  store i32 2, i32* %2
  br label %label.retBB1
label.falseBB1:
  br label %label.retBB1
label.retBB1:
  %5 = load i32, i32* %2
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %label.trueBB2, label %label.retBB2
label.trueBB2:
  store i32 4, i32* %2
  br label %label.retBB2
label.falseBB2:
  br label %label.retBB2
label.retBB2:
  %7 = load i32, i32* %2
  ret i32 %7
}
