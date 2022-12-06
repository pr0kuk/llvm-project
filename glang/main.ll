@show_window = internal global i32 0
@flag_no_recalc = internal global i32 0
@points = internal global [10 x [3 x i32]] zeroinitializer
@pixels = internal global [800 x [800 x [3 x i32]]] zeroinitializer
@a = internal global [3 x i32] zeroinitializer
@b = internal global [3 x i32] zeroinitializer
@sx = internal global [10 x i32] zeroinitializer
@sy = internal global [10 x i32] zeroinitializer
@ns = internal global [10 x i32] zeroinitializer
@t = internal global i32 0
@i = internal global i32 0
@j = internal global i32 0
@k = internal global i32 0
@d = internal global i32 0
@l = internal global i32 0
@c = internal global i32 0
@maxd = internal global i32 0
@retd = internal global i32 0

declare void @gl_init()

declare void @gl_start()

declare void @gl_put_pixel(i32, i32, i32)

declare void @print(i32)

declare void @gl_flush()

declare i32 @int_rand()

define void @dist() {
entry:
  %0 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @b, i32 0, i32 0), align 4
  %1 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @a, i32 0, i32 0), align 4
  %2 = sub i32 %0, %1
  %3 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @b, i32 0, i32 0), align 4
  %4 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @a, i32 0, i32 0), align 4
  %5 = sub i32 %3, %4
  %6 = mul i32 %2, %5
  %7 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @b, i32 0, i32 1), align 4
  %8 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @a, i32 0, i32 1), align 4
  %9 = sub i32 %7, %8
  %10 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @b, i32 0, i32 1), align 4
  %11 = load i32, i32* getelementptr inbounds ([3 x i32], [3 x i32]* @a, i32 0, i32 1), align 4
  %12 = sub i32 %10, %11
  %13 = mul i32 %9, %12
  %14 = add i32 %6, %13
  store i32 %14, i32* @retd, align 4
  ret void
}

define void @calc_new_centers() {
entry:
  store i32 0, i32* @i, align 4
  br label %0

0:                                                ; preds = %4, %entry
  %1 = load i32, i32* @i, align 4
  %2 = icmp slt i32 %1, 10
  br i1 %2, label %4, label %3

3:                                                ; preds = %0
  store i32 0, i32* @i, align 4
  br label %13

4:                                                ; preds = %0
  %5 = load i32, i32* @i, align 4
  %6 = getelementptr [10 x i32], [10 x i32]* @sx, i32 0, i32 %5
  store i32 0, i32* %6, align 4
  %7 = load i32, i32* @i, align 4
  %8 = getelementptr [10 x i32], [10 x i32]* @sy, i32 0, i32 %7
  store i32 0, i32* %8, align 4
  %9 = load i32, i32* @i, align 4
  %10 = getelementptr [10 x i32], [10 x i32]* @ns, i32 0, i32 %9
  store i32 0, i32* %10, align 4
  %11 = load i32, i32* @i, align 4
  %12 = add i32 %11, 1
  store i32 %12, i32* @i, align 4
  br label %0

13:                                               ; preds = %21, %3
  %14 = load i32, i32* @i, align 4
  %15 = icmp slt i32 %14, 800
  br i1 %15, label %17, label %16

16:                                               ; preds = %13
  store i32 0, i32* @i, align 4
  br label %80

17:                                               ; preds = %13
  store i32 0, i32* @j, align 4
  br label %18

18:                                               ; preds = %77, %17
  %19 = load i32, i32* @j, align 4
  %20 = icmp slt i32 %19, 800
  br i1 %20, label %24, label %21

21:                                               ; preds = %18
  %22 = load i32, i32* @i, align 4
  %23 = add i32 %22, 1
  store i32 %23, i32* @i, align 4
  br label %13

24:                                               ; preds = %18
  %25 = load i32, i32* @i, align 4
  %26 = load i32, i32* @j, align 4
  %27 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %25, i32 %26, i32 2
  %28 = load i32, i32* %27, align 4
  %29 = icmp sge i32 %28, 0
  %30 = zext i1 %29 to i32
  %31 = icmp ne i32 %30, 0
  br i1 %31, label %32, label %77

32:                                               ; preds = %24
  %33 = load i32, i32* @i, align 4
  %34 = load i32, i32* @j, align 4
  %35 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %33, i32 %34, i32 2
  %36 = load i32, i32* %35, align 4
  %37 = getelementptr [10 x i32], [10 x i32]* @sx, i32 0, i32 %36
  %38 = load i32, i32* @i, align 4
  %39 = load i32, i32* @j, align 4
  %40 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %38, i32 %39, i32 2
  %41 = load i32, i32* %40, align 4
  %42 = getelementptr [10 x i32], [10 x i32]* @sx, i32 0, i32 %41
  %43 = load i32, i32* %42, align 4
  %44 = load i32, i32* @i, align 4
  %45 = load i32, i32* @j, align 4
  %46 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %44, i32 %45, i32 0
  %47 = load i32, i32* %46, align 4
  %48 = add i32 %43, %47
  store i32 %48, i32* %37, align 4
  %49 = load i32, i32* @i, align 4
  %50 = load i32, i32* @j, align 4
  %51 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %49, i32 %50, i32 2
  %52 = load i32, i32* %51, align 4
  %53 = getelementptr [10 x i32], [10 x i32]* @sy, i32 0, i32 %52
  %54 = load i32, i32* @i, align 4
  %55 = load i32, i32* @j, align 4
  %56 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %54, i32 %55, i32 2
  %57 = load i32, i32* %56, align 4
  %58 = getelementptr [10 x i32], [10 x i32]* @sy, i32 0, i32 %57
  %59 = load i32, i32* %58, align 4
  %60 = load i32, i32* @i, align 4
  %61 = load i32, i32* @j, align 4
  %62 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %60, i32 %61, i32 1
  %63 = load i32, i32* %62, align 4
  %64 = add i32 %59, %63
  store i32 %64, i32* %53, align 4
  %65 = load i32, i32* @i, align 4
  %66 = load i32, i32* @j, align 4
  %67 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %65, i32 %66, i32 2
  %68 = load i32, i32* %67, align 4
  %69 = getelementptr [10 x i32], [10 x i32]* @ns, i32 0, i32 %68
  %70 = load i32, i32* @i, align 4
  %71 = load i32, i32* @j, align 4
  %72 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %70, i32 %71, i32 2
  %73 = load i32, i32* %72, align 4
  %74 = getelementptr [10 x i32], [10 x i32]* @ns, i32 0, i32 %73
  %75 = load i32, i32* %74, align 4
  %76 = add i32 %75, 1
  store i32 %76, i32* %69, align 4
  br label %77

77:                                               ; preds = %32, %24
  %78 = load i32, i32* @j, align 4
  %79 = add i32 %78, 1
  store i32 %79, i32* @j, align 4
  br label %18

80:                                               ; preds = %122, %16
  %81 = load i32, i32* @i, align 4
  %82 = icmp slt i32 %81, 10
  br i1 %82, label %84, label %83

83:                                               ; preds = %80
  ret void

84:                                               ; preds = %80
  %85 = load i32, i32* @i, align 4
  %86 = getelementptr [10 x i32], [10 x i32]* @sx, i32 0, i32 %85
  %87 = load i32, i32* %86, align 4
  %88 = load i32, i32* @i, align 4
  %89 = getelementptr [10 x i32], [10 x i32]* @ns, i32 0, i32 %88
  %90 = load i32, i32* %89, align 4
  %91 = sdiv i32 %87, %90
  store i32 %91, i32* @t, align 4
  %92 = load i32, i32* @i, align 4
  %93 = getelementptr [10 x [3 x i32]], [10 x [3 x i32]]* @points, i32 0, i32 %92, i32 0
  %94 = load i32, i32* %93, align 4
  %95 = load i32, i32* @t, align 4
  %96 = icmp ne i32 %94, %95
  %97 = zext i1 %96 to i32
  %98 = icmp ne i32 %97, 0
  br i1 %98, label %99, label %103

99:                                               ; preds = %84
  %100 = load i32, i32* @i, align 4
  %101 = getelementptr [10 x [3 x i32]], [10 x [3 x i32]]* @points, i32 0, i32 %100, i32 0
  %102 = load i32, i32* @t, align 4
  store i32 %102, i32* %101, align 4
  br label %103

103:                                              ; preds = %99, %84
  %104 = load i32, i32* @i, align 4
  %105 = getelementptr [10 x i32], [10 x i32]* @sy, i32 0, i32 %104
  %106 = load i32, i32* %105, align 4
  %107 = load i32, i32* @i, align 4
  %108 = getelementptr [10 x i32], [10 x i32]* @ns, i32 0, i32 %107
  %109 = load i32, i32* %108, align 4
  %110 = sdiv i32 %106, %109
  store i32 %110, i32* @t, align 4
  %111 = load i32, i32* @i, align 4
  %112 = getelementptr [10 x [3 x i32]], [10 x [3 x i32]]* @points, i32 0, i32 %111, i32 1
  %113 = load i32, i32* %112, align 4
  %114 = load i32, i32* @t, align 4
  %115 = icmp ne i32 %113, %114
  %116 = zext i1 %115 to i32
  %117 = icmp ne i32 %116, 0
  br i1 %117, label %118, label %122

118:                                              ; preds = %103
  %119 = load i32, i32* @i, align 4
  %120 = getelementptr [10 x [3 x i32]], [10 x [3 x i32]]* @points, i32 0, i32 %119, i32 1
  %121 = load i32, i32* @t, align 4
  store i32 %121, i32* %120, align 4
  br label %122

122:                                              ; preds = %118, %103
  %123 = load i32, i32* @i, align 4
  %124 = add i32 %123, 1
  store i32 %124, i32* @i, align 4
  br label %80
}

define void @calc_vor_diag() {
entry:
  store i32 0, i32* @i, align 4
  br label %0

0:                                                ; preds = %8, %entry
  %1 = load i32, i32* @i, align 4
  %2 = icmp slt i32 %1, 800
  br i1 %2, label %4, label %3

3:                                                ; preds = %0
  ret void

4:                                                ; preds = %0
  store i32 1000000000, i32* @maxd, align 4
  store i32 0, i32* @d, align 4
  br label %5

5:                                                ; preds = %21, %4
  %6 = load i32, i32* @d, align 4
  %7 = icmp slt i32 %6, 800
  br i1 %7, label %11, label %8

8:                                                ; preds = %5
  %9 = load i32, i32* @i, align 4
  %10 = add i32 %9, 1
  store i32 %10, i32* @i, align 4
  br label %0

11:                                               ; preds = %5
  store i32 0, i32* @k, align 4
  br label %12

12:                                               ; preds = %64, %11
  %13 = load i32, i32* @k, align 4
  %14 = icmp slt i32 %13, 10
  %15 = zext i1 %14 to i32
  %16 = load i32, i32* @maxd, align 4
  %17 = icmp sgt i32 %16, 0
  %18 = zext i1 %17 to i32
  %19 = and i32 %15, %18
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %32, label %21

21:                                               ; preds = %12
  store i32 1000000000, i32* @maxd, align 4
  %22 = load i32, i32* @i, align 4
  %23 = load i32, i32* @d, align 4
  %24 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %22, i32 %23, i32 0
  %25 = load i32, i32* @d, align 4
  store i32 %25, i32* %24, align 4
  %26 = load i32, i32* @i, align 4
  %27 = load i32, i32* @d, align 4
  %28 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %26, i32 %27, i32 1
  %29 = load i32, i32* @i, align 4
  store i32 %29, i32* %28, align 4
  %30 = load i32, i32* @d, align 4
  %31 = add i32 %30, 1
  store i32 %31, i32* @d, align 4
  br label %5

32:                                               ; preds = %12
  store i32 0, i32* @l, align 4
  br label %33

33:                                               ; preds = %42, %32
  %34 = load i32, i32* @l, align 4
  %35 = icmp slt i32 %34, 3
  br i1 %35, label %42, label %36

36:                                               ; preds = %33
  call void @dist()
  %37 = load i32, i32* @retd, align 4
  %38 = load i32, i32* @maxd, align 4
  %39 = icmp slt i32 %37, %38
  %40 = zext i1 %39 to i32
  %41 = icmp ne i32 %40, 0
  br i1 %41, label %58, label %64

42:                                               ; preds = %33
  %43 = load i32, i32* @l, align 4
  %44 = getelementptr [3 x i32], [3 x i32]* @a, i32 0, i32 %43
  %45 = load i32, i32* @i, align 4
  %46 = load i32, i32* @d, align 4
  %47 = load i32, i32* @l, align 4
  %48 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %45, i32 %46, i32 %47
  %49 = load i32, i32* %48, align 4
  store i32 %49, i32* %44, align 4
  %50 = load i32, i32* @l, align 4
  %51 = getelementptr [3 x i32], [3 x i32]* @b, i32 0, i32 %50
  %52 = load i32, i32* @k, align 4
  %53 = load i32, i32* @l, align 4
  %54 = getelementptr [10 x [3 x i32]], [10 x [3 x i32]]* @points, i32 0, i32 %52, i32 %53
  %55 = load i32, i32* %54, align 4
  store i32 %55, i32* %51, align 4
  %56 = load i32, i32* @l, align 4
  %57 = add i32 %56, 1
  store i32 %57, i32* @l, align 4
  br label %33

58:                                               ; preds = %36
  %59 = load i32, i32* @retd, align 4
  store i32 %59, i32* @maxd, align 4
  %60 = load i32, i32* @i, align 4
  %61 = load i32, i32* @d, align 4
  %62 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %60, i32 %61, i32 2
  %63 = load i32, i32* @k, align 4
  store i32 %63, i32* %62, align 4
  br label %64

64:                                               ; preds = %58, %36
  %65 = load i32, i32* @k, align 4
  %66 = add i32 %65, 1
  store i32 %66, i32* @k, align 4
  br label %12
}

define void @display() {
entry:
  call void @calc_vor_diag()
  call void @gl_start()
  store i32 0, i32* @i, align 4
  br label %0

0:                                                ; preds = %8, %entry
  %1 = load i32, i32* @i, align 4
  %2 = icmp slt i32 %1, 800
  br i1 %2, label %4, label %3

3:                                                ; preds = %0
  call void @gl_flush()
  ret void

4:                                                ; preds = %0
  store i32 0, i32* @j, align 4
  br label %5

5:                                                ; preds = %11, %4
  %6 = load i32, i32* @j, align 4
  %7 = icmp slt i32 %6, 800
  br i1 %7, label %11, label %8

8:                                                ; preds = %5
  %9 = load i32, i32* @i, align 4
  %10 = add i32 %9, 1
  store i32 %10, i32* @i, align 4
  br label %0

11:                                               ; preds = %5
  %12 = load i32, i32* @j, align 4
  %13 = load i32, i32* @i, align 4
  %14 = load i32, i32* @i, align 4
  %15 = load i32, i32* @j, align 4
  %16 = getelementptr [800 x [800 x [3 x i32]]], [800 x [800 x [3 x i32]]]* @pixels, i32 0, i32 %14, i32 %15, i32 2
  %17 = load i32, i32* %16, align 4
  call void @gl_put_pixel(i32 %12, i32 %13, i32 %17)
  %18 = load i32, i32* @j, align 4
  %19 = add i32 %18, 1
  store i32 %19, i32* @j, align 4
  br label %5
}

define void @loop() {
entry:
  call void @display()
  br label %0

0:                                                ; preds = %2, %entry
  br i1 true, label %2, label %1

1:                                                ; preds = %0
  ret void

2:                                                ; preds = %0
  call void @calc_new_centers()
  call void @display()
  br label %0
}

define void @reset_picture() {
entry:
  store i32 0, i32* @i, align 4
  br label %0

0:                                                ; preds = %4, %entry
  %1 = load i32, i32* @i, align 4
  %2 = icmp slt i32 %1, 10
  br i1 %2, label %4, label %3

3:                                                ; preds = %0
  call void @calc_vor_diag()
  ret void

4:                                                ; preds = %0
  %5 = call i32 @int_rand()
  store i32 %5, i32* @c, align 4
  %6 = load i32, i32* @i, align 4
  %7 = getelementptr [10 x [3 x i32]], [10 x [3 x i32]]* @points, i32 0, i32 %6, i32 0
  %8 = load i32, i32* @c, align 4
  %9 = srem i32 %8, 800
  store i32 %9, i32* %7, align 4
  %10 = call i32 @int_rand()
  store i32 %10, i32* @c, align 4
  %11 = load i32, i32* @i, align 4
  %12 = getelementptr [10 x [3 x i32]], [10 x [3 x i32]]* @points, i32 0, i32 %11, i32 1
  %13 = load i32, i32* @c, align 4
  %14 = srem i32 %13, 800
  store i32 %14, i32* %12, align 4
  %15 = load i32, i32* @i, align 4
  %16 = add i32 %15, 1
  store i32 %16, i32* @i, align 4
  br label %0
}

define void @main() {
entry:
  call void @gl_init()
  call void @reset_picture()
  call void @loop()
  ret void
}