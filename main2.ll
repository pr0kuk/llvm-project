; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.Point = type { i32, i32, i32 }

@pixels = internal global [800 x [800 x %struct.Point]] zeroinitializer, align 16
@points = internal unnamed_addr global [10 x %struct.Point] zeroinitializer, align 16
@flag_no_recalc = internal unnamed_addr global i1 false, align 4
@show_window = internal unnamed_addr global i1 false, align 4

; Function Attrs: norecurse nounwind readonly uwtable
define dso_local i32 @dist(%struct.Point* nocapture readonly %0, %struct.Point* nocapture readonly %1) local_unnamed_addr #0 {
  %3 = getelementptr inbounds %struct.Point, %struct.Point* %1, i64 0, i32 1
  %4 = load i32, i32* %3, align 4, !tbaa !2
  %5 = getelementptr inbounds %struct.Point, %struct.Point* %0, i64 0, i32 1
  %6 = load i32, i32* %5, align 4, !tbaa !2
  %7 = sub nsw i32 %4, %6
  %8 = mul nsw i32 %7, %7
  %9 = getelementptr inbounds %struct.Point, %struct.Point* %1, i64 0, i32 2
  %10 = load i32, i32* %9, align 4, !tbaa !7
  %11 = getelementptr inbounds %struct.Point, %struct.Point* %0, i64 0, i32 2
  %12 = load i32, i32* %11, align 4, !tbaa !7
  %13 = sub nsw i32 %10, %12
  %14 = mul nsw i32 %13, %13
  %15 = add nuw nsw i32 %14, %8
  ret i32 %15
}

; Function Attrs: nounwind uwtable
define dso_local i32 @calc_new_centers([800 x %struct.Point]* nocapture readonly %0, %struct.Point* nocapture %1) local_unnamed_addr #1 {
  %3 = alloca [10 x i32], align 16
  %4 = bitcast [10 x i32]* %3 to i8*
  %5 = alloca [10 x i32], align 16
  %6 = bitcast [10 x i32]* %5 to i8*
  %7 = alloca [10 x i32], align 16
  %8 = bitcast [10 x i32]* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %4) #7
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %6) #7
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %8) #7
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(40) %4, i8 0, i64 40, i1 false)
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(40) %6, i8 0, i64 40, i1 false)
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(40) %8, i8 0, i64 40, i1 false)
  br label %9

9:                                                ; preds = %11, %2
  %10 = phi i64 [ 0, %2 ], [ %12, %11 ]
  br label %14

11:                                               ; preds = %34
  %12 = add nuw nsw i64 %10, 1
  %13 = icmp eq i64 %12, 800
  br i1 %13, label %38, label %9

14:                                               ; preds = %34, %9
  %15 = phi i64 [ 0, %9 ], [ %35, %34 ]
  %16 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %0, i64 %10, i64 %15, i32 0
  %17 = load i32, i32* %16, align 4, !tbaa !8
  %18 = icmp sgt i32 %17, -1
  br i1 %18, label %19, label %34

19:                                               ; preds = %14
  %20 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %0, i64 %10, i64 %15, i32 1
  %21 = load i32, i32* %20, align 4, !tbaa !2
  %22 = zext i32 %17 to i64
  %23 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %22
  %24 = load i32, i32* %23, align 4, !tbaa !9
  %25 = add nsw i32 %24, %21
  store i32 %25, i32* %23, align 4, !tbaa !9
  %26 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %0, i64 %10, i64 %15, i32 2
  %27 = load i32, i32* %26, align 4, !tbaa !7
  %28 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %22
  %29 = load i32, i32* %28, align 4, !tbaa !9
  %30 = add nsw i32 %29, %27
  store i32 %30, i32* %28, align 4, !tbaa !9
  %31 = getelementptr inbounds [10 x i32], [10 x i32]* %7, i64 0, i64 %22
  %32 = load i32, i32* %31, align 4, !tbaa !9
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %31, align 4, !tbaa !9
  br label %34

34:                                               ; preds = %14, %19
  %35 = add nuw nsw i64 %15, 1
  %36 = icmp eq i64 %35, 800
  br i1 %36, label %11, label %14

37:                                               ; preds = %63
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %8) #7
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %6) #7
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %4) #7
  ret i32 %64

38:                                               ; preds = %11, %63
  %39 = phi i64 [ %65, %63 ], [ 0, %11 ]
  %40 = phi i32 [ %64, %63 ], [ 0, %11 ]
  %41 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %39
  %42 = load i32, i32* %41, align 4, !tbaa !9
  %43 = getelementptr inbounds [10 x i32], [10 x i32]* %7, i64 0, i64 %39
  %44 = load i32, i32* %43, align 4, !tbaa !9
  %45 = sdiv i32 %42, %44
  %46 = getelementptr inbounds %struct.Point, %struct.Point* %1, i64 %39, i32 1
  %47 = load i32, i32* %46, align 4, !tbaa !2
  %48 = icmp eq i32 %47, %45
  br i1 %48, label %49, label %51

49:                                               ; preds = %38
  %50 = add nsw i32 %40, 1
  br label %52

51:                                               ; preds = %38
  store i32 %45, i32* %46, align 4, !tbaa !2
  br label %52

52:                                               ; preds = %51, %49
  %53 = phi i32 [ %50, %49 ], [ %40, %51 ]
  %54 = getelementptr inbounds [10 x i32], [10 x i32]* %5, i64 0, i64 %39
  %55 = load i32, i32* %54, align 4, !tbaa !9
  %56 = sdiv i32 %55, %44
  %57 = getelementptr inbounds %struct.Point, %struct.Point* %1, i64 %39, i32 2
  %58 = load i32, i32* %57, align 4, !tbaa !7
  %59 = icmp eq i32 %58, %56
  br i1 %59, label %60, label %62

60:                                               ; preds = %52
  %61 = add nsw i32 %53, 1
  br label %63

62:                                               ; preds = %52
  store i32 %56, i32* %57, align 4, !tbaa !7
  br label %63

63:                                               ; preds = %60, %62
  %64 = phi i32 [ %61, %60 ], [ %53, %62 ]
  %65 = add nuw nsw i64 %39, 1
  %66 = icmp eq i64 %65, 10
  br i1 %66, label %37, label %38
}

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #2

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #2

; Function Attrs: nofree norecurse nounwind uwtable
define dso_local void @calc_vor_diag([800 x %struct.Point]* nocapture %0, %struct.Point* nocapture readonly %1) local_unnamed_addr #3 {
  br label %3

3:                                                ; preds = %14, %2
  %4 = phi i64 [ 0, %2 ], [ %15, %14 ]
  %5 = trunc i64 %4 to i32
  br label %7

6:                                                ; preds = %14
  ret void

7:                                                ; preds = %17, %3
  %8 = phi i64 [ 0, %3 ], [ %19, %17 ]
  %9 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %0, i64 %4, i64 %8, i32 1
  %10 = load i32, i32* %9, align 4, !tbaa !2
  %11 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %0, i64 %4, i64 %8, i32 2
  %12 = load i32, i32* %11, align 4, !tbaa !7
  %13 = getelementptr inbounds [800 x %struct.Point], [800 x %struct.Point]* %0, i64 %4, i64 %8, i32 0
  br label %21

14:                                               ; preds = %17
  %15 = add nuw nsw i64 %4, 1
  %16 = icmp eq i64 %15, 800
  br i1 %16, label %6, label %3

17:                                               ; preds = %36
  %18 = trunc i64 %8 to i32
  store i32 %18, i32* %9, align 4, !tbaa !2
  store i32 %5, i32* %11, align 4, !tbaa !7
  %19 = add nuw nsw i64 %8, 1
  %20 = icmp eq i64 %19, 800
  br i1 %20, label %14, label %7

21:                                               ; preds = %7, %36
  %22 = phi i64 [ 0, %7 ], [ %38, %36 ]
  %23 = phi i32 [ 1000000000, %7 ], [ %37, %36 ]
  %24 = getelementptr inbounds %struct.Point, %struct.Point* %1, i64 %22, i32 1
  %25 = load i32, i32* %24, align 4, !tbaa !2
  %26 = sub nsw i32 %25, %10
  %27 = mul nsw i32 %26, %26
  %28 = getelementptr inbounds %struct.Point, %struct.Point* %1, i64 %22, i32 2
  %29 = load i32, i32* %28, align 4, !tbaa !7
  %30 = sub nsw i32 %29, %12
  %31 = mul nsw i32 %30, %30
  %32 = add nuw nsw i32 %31, %27
  %33 = icmp slt i32 %32, %23
  br i1 %33, label %34, label %36

34:                                               ; preds = %21
  %35 = trunc i64 %22 to i32
  store i32 %35, i32* %13, align 4, !tbaa !8
  br label %36

36:                                               ; preds = %21, %34
  %37 = phi i32 [ %32, %34 ], [ %23, %21 ]
  %38 = add nuw nsw i64 %22, 1
  %39 = icmp ult i64 %22, 9
  %40 = icmp sgt i32 %37, 0
  %41 = and i1 %40, %39
  br i1 %41, label %21, label %17
}

; Function Attrs: nounwind uwtable
define dso_local void @display() local_unnamed_addr #1 {
  br label %1

1:                                                ; preds = %11, %0
  %2 = phi i64 [ 0, %0 ], [ %12, %11 ]
  %3 = trunc i64 %2 to i32
  br label %4

4:                                                ; preds = %14, %1
  %5 = phi i64 [ 0, %1 ], [ %16, %14 ]
  %6 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 1
  %7 = load i32, i32* %6, align 4, !tbaa !2
  %8 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 2
  %9 = load i32, i32* %8, align 4, !tbaa !7
  %10 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 0
  br label %18

11:                                               ; preds = %14
  %12 = add nuw nsw i64 %2, 1
  %13 = icmp eq i64 %12, 800
  br i1 %13, label %39, label %1

14:                                               ; preds = %33
  %15 = trunc i64 %5 to i32
  store i32 %15, i32* %6, align 4, !tbaa !2
  store i32 %3, i32* %8, align 4, !tbaa !7
  %16 = add nuw nsw i64 %5, 1
  %17 = icmp eq i64 %16, 800
  br i1 %17, label %11, label %4

18:                                               ; preds = %33, %4
  %19 = phi i64 [ 0, %4 ], [ %35, %33 ]
  %20 = phi i32 [ 1000000000, %4 ], [ %34, %33 ]
  %21 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 1
  %22 = load i32, i32* %21, align 4, !tbaa !2
  %23 = sub nsw i32 %22, %7
  %24 = mul nsw i32 %23, %23
  %25 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 2
  %26 = load i32, i32* %25, align 4, !tbaa !7
  %27 = sub nsw i32 %26, %9
  %28 = mul nsw i32 %27, %27
  %29 = add nuw nsw i32 %28, %24
  %30 = icmp slt i32 %29, %20
  br i1 %30, label %31, label %33

31:                                               ; preds = %18
  %32 = trunc i64 %19 to i32
  store i32 %32, i32* %10, align 4, !tbaa !8
  br label %33

33:                                               ; preds = %31, %18
  %34 = phi i32 [ %29, %31 ], [ %20, %18 ]
  %35 = add nuw nsw i64 %19, 1
  %36 = icmp ult i64 %19, 9
  %37 = icmp sgt i32 %34, 0
  %38 = and i1 %36, %37
  br i1 %38, label %18, label %14

39:                                               ; preds = %11
  tail call void (...) @gl_start() #7
  br label %40

40:                                               ; preds = %43, %39
  %41 = phi i64 [ 0, %39 ], [ %44, %43 ]
  br label %46

42:                                               ; preds = %43
  tail call void (...) @gl_flush() #7
  ret void

43:                                               ; preds = %46
  %44 = add nuw nsw i64 %41, 1
  %45 = icmp eq i64 %44, 800
  br i1 %45, label %42, label %40

46:                                               ; preds = %46, %40
  %47 = phi i64 [ 0, %40 ], [ %49, %46 ]
  %48 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %41, i64 %47
  tail call void @gl_put_pixel(%struct.Point* nonnull %48) #7
  %49 = add nuw nsw i64 %47, 1
  %50 = icmp eq i64 %49, 800
  br i1 %50, label %43, label %46
}

declare dso_local void @gl_start(...) local_unnamed_addr #4

declare dso_local void @gl_put_pixel(%struct.Point*) local_unnamed_addr #4

declare dso_local void @gl_flush(...) local_unnamed_addr #4

; Function Attrs: nounwind uwtable
define dso_local void @timf(i32 %0) local_unnamed_addr #1 {
  %2 = alloca [10 x i32], align 16
  %3 = alloca [10 x i32], align 16
  %4 = alloca [10 x i32], align 16
  %5 = load i1, i1* @flag_no_recalc, align 4
  br i1 %5, label %71, label %6

6:                                                ; preds = %1
  %7 = bitcast [10 x i32]* %2 to i8*
  %8 = bitcast [10 x i32]* %3 to i8*
  %9 = bitcast [10 x i32]* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %7) #7
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %8) #7
  call void @llvm.lifetime.start.p0i8(i64 40, i8* nonnull %9) #7
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(40) %7, i8 0, i64 40, i1 false) #7
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(40) %8, i8 0, i64 40, i1 false) #7
  call void @llvm.memset.p0i8.i64(i8* nonnull align 16 dereferenceable(40) %9, i8 0, i64 40, i1 false) #7
  br label %10

10:                                               ; preds = %12, %6
  %11 = phi i64 [ 0, %6 ], [ %13, %12 ]
  br label %15

12:                                               ; preds = %35
  %13 = add nuw nsw i64 %11, 1
  %14 = icmp eq i64 %13, 800
  br i1 %14, label %38, label %10

15:                                               ; preds = %35, %10
  %16 = phi i64 [ 0, %10 ], [ %36, %35 ]
  %17 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %11, i64 %16, i32 0
  %18 = load i32, i32* %17, align 4, !tbaa !8
  %19 = icmp sgt i32 %18, -1
  br i1 %19, label %20, label %35

20:                                               ; preds = %15
  %21 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %11, i64 %16, i32 1
  %22 = load i32, i32* %21, align 4, !tbaa !2
  %23 = zext i32 %18 to i64
  %24 = getelementptr inbounds [10 x i32], [10 x i32]* %2, i64 0, i64 %23
  %25 = load i32, i32* %24, align 4, !tbaa !9
  %26 = add nsw i32 %25, %22
  store i32 %26, i32* %24, align 4, !tbaa !9
  %27 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %11, i64 %16, i32 2
  %28 = load i32, i32* %27, align 4, !tbaa !7
  %29 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %23
  %30 = load i32, i32* %29, align 4, !tbaa !9
  %31 = add nsw i32 %30, %28
  store i32 %31, i32* %29, align 4, !tbaa !9
  %32 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %23
  %33 = load i32, i32* %32, align 4, !tbaa !9
  %34 = add nsw i32 %33, 1
  store i32 %34, i32* %32, align 4, !tbaa !9
  br label %35

35:                                               ; preds = %20, %15
  %36 = add nuw nsw i64 %16, 1
  %37 = icmp eq i64 %36, 800
  br i1 %37, label %12, label %15

38:                                               ; preds = %12, %63
  %39 = phi i64 [ %65, %63 ], [ 0, %12 ]
  %40 = phi i32 [ %64, %63 ], [ 0, %12 ]
  %41 = getelementptr inbounds [10 x i32], [10 x i32]* %2, i64 0, i64 %39
  %42 = load i32, i32* %41, align 4, !tbaa !9
  %43 = getelementptr inbounds [10 x i32], [10 x i32]* %4, i64 0, i64 %39
  %44 = load i32, i32* %43, align 4, !tbaa !9
  %45 = sdiv i32 %42, %44
  %46 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %39, i32 1
  %47 = load i32, i32* %46, align 4, !tbaa !2
  %48 = icmp eq i32 %47, %45
  br i1 %48, label %49, label %51

49:                                               ; preds = %38
  %50 = add nsw i32 %40, 1
  br label %52

51:                                               ; preds = %38
  store i32 %45, i32* %46, align 4, !tbaa !2
  br label %52

52:                                               ; preds = %51, %49
  %53 = phi i32 [ %50, %49 ], [ %40, %51 ]
  %54 = getelementptr inbounds [10 x i32], [10 x i32]* %3, i64 0, i64 %39
  %55 = load i32, i32* %54, align 4, !tbaa !9
  %56 = sdiv i32 %55, %44
  %57 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %39, i32 2
  %58 = load i32, i32* %57, align 4, !tbaa !7
  %59 = icmp eq i32 %58, %56
  br i1 %59, label %60, label %62

60:                                               ; preds = %52
  %61 = add nsw i32 %53, 1
  br label %63

62:                                               ; preds = %52
  store i32 %56, i32* %57, align 4, !tbaa !7
  br label %63

63:                                               ; preds = %62, %60
  %64 = phi i32 [ %61, %60 ], [ %53, %62 ]
  %65 = add nuw nsw i64 %39, 1
  %66 = icmp eq i64 %65, 10
  br i1 %66, label %67, label %38

67:                                               ; preds = %63
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %9) #7
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %8) #7
  call void @llvm.lifetime.end.p0i8(i64 40, i8* nonnull %7) #7
  %68 = icmp slt i32 %64, 20
  br i1 %68, label %69, label %70

69:                                               ; preds = %67
  tail call void @display()
  br label %71

70:                                               ; preds = %67
  store i1 true, i1* @flag_no_recalc, align 4
  br label %71

71:                                               ; preds = %1, %69, %70
  ret void
}

; Function Attrs: norecurse nounwind readnone uwtable
define dso_local void @set_timer(i32 %0) local_unnamed_addr #5 {
  ret void
}

; Function Attrs: nounwind uwtable
define dso_local void @reset_picture() local_unnamed_addr #1 {
  br label %40

1:                                                ; preds = %40, %11
  %2 = phi i64 [ %12, %11 ], [ 0, %40 ]
  %3 = trunc i64 %2 to i32
  br label %4

4:                                                ; preds = %14, %1
  %5 = phi i64 [ 0, %1 ], [ %16, %14 ]
  %6 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 1
  %7 = load i32, i32* %6, align 4, !tbaa !2
  %8 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 2
  %9 = load i32, i32* %8, align 4, !tbaa !7
  %10 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 0
  br label %18

11:                                               ; preds = %14
  %12 = add nuw nsw i64 %2, 1
  %13 = icmp eq i64 %12, 800
  br i1 %13, label %39, label %1

14:                                               ; preds = %33
  %15 = trunc i64 %5 to i32
  store i32 %15, i32* %6, align 4, !tbaa !2
  store i32 %3, i32* %8, align 4, !tbaa !7
  %16 = add nuw nsw i64 %5, 1
  %17 = icmp eq i64 %16, 800
  br i1 %17, label %11, label %4

18:                                               ; preds = %33, %4
  %19 = phi i64 [ 0, %4 ], [ %35, %33 ]
  %20 = phi i32 [ 1000000000, %4 ], [ %34, %33 ]
  %21 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 1
  %22 = load i32, i32* %21, align 4, !tbaa !2
  %23 = sub nsw i32 %22, %7
  %24 = mul nsw i32 %23, %23
  %25 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 2
  %26 = load i32, i32* %25, align 4, !tbaa !7
  %27 = sub nsw i32 %26, %9
  %28 = mul nsw i32 %27, %27
  %29 = add nuw nsw i32 %28, %24
  %30 = icmp slt i32 %29, %20
  br i1 %30, label %31, label %33

31:                                               ; preds = %18
  %32 = trunc i64 %19 to i32
  store i32 %32, i32* %10, align 4, !tbaa !8
  br label %33

33:                                               ; preds = %31, %18
  %34 = phi i32 [ %29, %31 ], [ %20, %18 ]
  %35 = add nuw nsw i64 %19, 1
  %36 = icmp ult i64 %19, 9
  %37 = icmp sgt i32 %34, 0
  %38 = and i1 %36, %37
  br i1 %38, label %18, label %14

39:                                               ; preds = %11
  store i1 false, i1* @flag_no_recalc, align 4
  ret void

40:                                               ; preds = %40, %0
  %41 = phi i64 [ 0, %0 ], [ %48, %40 ]
  %42 = tail call i32 (...) @int_rand() #7
  %43 = srem i32 %42, 800
  %44 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %41, i32 1
  store i32 %43, i32* %44, align 4, !tbaa !2
  %45 = tail call i32 (...) @int_rand() #7
  %46 = srem i32 %45, 800
  %47 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %41, i32 2
  store i32 %46, i32* %47, align 4, !tbaa !7
  %48 = add nuw nsw i64 %41, 1
  %49 = icmp eq i64 %48, 10
  br i1 %49, label %1, label %40
}

declare dso_local i32 @int_rand(...) local_unnamed_addr #4

; Function Attrs: nounwind uwtable
define dso_local void @loop() local_unnamed_addr #1 {
  tail call void @display()
  %1 = load i1, i1* @show_window, align 4
  br i1 %1, label %4, label %2

2:                                                ; preds = %0, %2
  tail call void @timf(i32 10)
  %3 = load i1, i1* @show_window, align 4
  br i1 %3, label %4, label %2

4:                                                ; preds = %2, %0
  ret void
}

; Function Attrs: nofree norecurse nounwind uwtable writeonly
define dso_local void @exit_loop() local_unnamed_addr #6 {
  store i1 true, i1* @show_window, align 4
  ret void
}

; Function Attrs: nounwind uwtable
define dso_local i32 @main(i32 %0, i8** %1) local_unnamed_addr #1 {
  tail call void @gl_init(i32 %0, i8** %1) #7
  tail call void @reset_picture()
  tail call void @display() #7
  %3 = load i1, i1* @show_window, align 4
  br i1 %3, label %6, label %4

4:                                                ; preds = %2, %4
  tail call void @timf(i32 10) #7
  %5 = load i1, i1* @show_window, align 4
  br i1 %5, label %6, label %4

6:                                                ; preds = %4, %2
  ret i32 0
}

declare dso_local void @gl_init(i32, i8**) local_unnamed_addr #4

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #2

attributes #0 = { norecurse nounwind readonly uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { argmemonly nounwind willreturn }
attributes #3 = { nofree norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { norecurse nounwind readnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nofree norecurse nounwind uwtable writeonly "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
!2 = !{!3, !4, i64 4}
!3 = !{!"Point", !4, i64 0, !4, i64 4, !4, i64 8}
!4 = !{!"int", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C/C++ TBAA"}
!7 = !{!3, !4, i64 8}
!8 = !{!3, !4, i64 0}
!9 = !{!4, !4, i64 0}
