; ModuleID = '../interface.c'
source_filename = "../interface.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [6 x i8] c"Lloyd\00", align 1

; Function Attrs: noinline optnone uwtable
define dso_local void @gl_start() #0 {
  call void @glClear(i32 16384)
  call void @glBegin(i32 0)
  ret void
}

declare dso_local void @glClear(i32) #1

declare dso_local void @glBegin(i32) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_Z6getrgbiPf(i32 %0, float* %1) #2 {
  %3 = alloca i32, align 4
  %4 = alloca float*, align 8
  store i32 %0, i32* %3, align 4
  store float* %1, float** %4, align 8
  br label %5

5:                                                ; preds = %16, %2
  %6 = load i32, i32* %3, align 4
  %7 = icmp sgt i32 %6, 0
  br i1 %7, label %8, label %19

8:                                                ; preds = %5
  %9 = load float*, float** %4, align 8
  %10 = load i32, i32* %3, align 4
  %11 = srem i32 %10, 3
  %12 = sext i32 %11 to i64
  %13 = getelementptr inbounds float, float* %9, i64 %12
  %14 = load float, float* %13, align 4
  %15 = fadd float %14, 0x3FD3333340000000
  store float %15, float* %13, align 4
  br label %16

16:                                               ; preds = %8
  %17 = load i32, i32* %3, align 4
  %18 = sdiv i32 %17, 3
  store i32 %18, i32* %3, align 4
  br label %5

19:                                               ; preds = %5
  ret void
}

; Function Attrs: noinline optnone uwtable
define dso_local void @gl_put_pixel(i32 %0, i32 %1, i32 %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca [3 x float], align 4
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  %8 = bitcast [3 x float]* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 4 %8, i8 0, i64 12, i1 false)
  %9 = load i32, i32* %6, align 4
  %10 = getelementptr inbounds [3 x float], [3 x float]* %7, i64 0, i64 0
  call void @_Z6getrgbiPf(i32 %9, float* %10)
  %11 = getelementptr inbounds [3 x float], [3 x float]* %7, i64 0, i64 0
  %12 = load float, float* %11, align 4
  %13 = getelementptr inbounds [3 x float], [3 x float]* %7, i64 0, i64 1
  %14 = load float, float* %13, align 4
  %15 = getelementptr inbounds [3 x float], [3 x float]* %7, i64 0, i64 2
  %16 = load float, float* %15, align 4
  call void @glColor3f(float %12, float %14, float %16)
  %17 = load i32, i32* %4, align 4
  %18 = sitofp i32 %17 to float
  %19 = fdiv float %18, 8.000000e+02
  %20 = fpext float %19 to double
  %21 = fsub double %20, 5.000000e-01
  %22 = fmul double %21, 2.000000e+00
  %23 = fptrunc double %22 to float
  %24 = load i32, i32* %5, align 4
  %25 = sitofp i32 %24 to float
  %26 = fdiv float %25, 8.000000e+02
  %27 = fpext float %26 to double
  %28 = fsub double %27, 5.000000e-01
  %29 = fmul double %28, 2.000000e+00
  %30 = fptrunc double %29 to float
  call void @glVertex2f(float %23, float %30)
  ret void
}

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #3

declare dso_local void @glColor3f(float, float, float) #1

declare dso_local void @glVertex2f(float, float) #1

; Function Attrs: noinline optnone uwtable
define dso_local void @gl_flush() #0 {
  call void @glEnd()
  call void @glFlush()
  ret void
}

declare dso_local void @glEnd() #1

declare dso_local void @glFlush() #1

; Function Attrs: noinline optnone uwtable
define dso_local void @gl_init() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i8**, align 8
  store i32 0, i32* %1, align 4
  %3 = load i8**, i8*** %2, align 8
  call void @glutInit(i32* %1, i8** %3)
  call void @glutInitDisplayMode(i32 0)
  call void @glutInitWindowPosition(i32 1000, i32 90)
  call void @glutInitWindowSize(i32 800, i32 800)
  %4 = call i32 @glutCreateWindow(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0))
  call void @glutIgnoreKeyRepeat(i32 1)
  ret void
}

declare dso_local void @glutInit(i32*, i8**) #1

declare dso_local void @glutInitDisplayMode(i32) #1

declare dso_local void @glutInitWindowPosition(i32, i32) #1

declare dso_local void @glutInitWindowSize(i32, i32) #1

declare dso_local i32 @glutCreateWindow(i8*) #1

declare dso_local void @glutIgnoreKeyRepeat(i32) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @int_rand() #2 {
  %1 = call i32 @rand() #5
  ret i32 %1
}

; Function Attrs: nounwind
declare dso_local i32 @rand() #4

attributes #0 = { noinline optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind willreturn }
attributes #4 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
