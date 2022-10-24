#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include <iostream>
#include <string>
#include <unordered_map>
void reset_picture();
void gl_init(int argc, char** argv);
void loop();


void LLVM_main() {
    std::cout << "ALIVE!!" << std::endl;
    // gl_init(argc, argv);
    // reset_picture();
    // loop();
}

void dump_codegen(llvm::Module* module) {
    std::string s;
    llvm::raw_string_ostream os(s);
    module->print(os, nullptr);
    os.flush();
    std::cout << s;
}

void display_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& displayFunc = module->getFunction("display");
    id2bb[1] = llvm::BasicBlock::Create(module->getContext(), "1", displayFunc );
    id2bb[4] = llvm::BasicBlock::Create(module->getContext(), "4", displayFunc );
    id2bb[11] = llvm::BasicBlock::Create(module->getContext(), "11", displayFunc );
    id2bb[14] = llvm::BasicBlock::Create(module->getContext(), "14", displayFunc );
    id2bb[18] = llvm::BasicBlock::Create(module->getContext(), "18", displayFunc );
    id2bb[31] = llvm::BasicBlock::Create(module->getContext(), "31", displayFunc );
    id2bb[33] = llvm::BasicBlock::Create(module->getContext(), "33", displayFunc );
    id2bb[39] = llvm::BasicBlock::Create(module->getContext(), "39", displayFunc );
    id2bb[40] = llvm::BasicBlock::Create(module->getContext(), "40", displayFunc );
    id2bb[42] = llvm::BasicBlock::Create(module->getContext(), "42", displayFunc );
    id2bb[43] = llvm::BasicBlock::Create(module->getContext(), "43", displayFunc );
    id2bb[46] = llvm::BasicBlock::Create(module->getContext(), "46", displayFunc );

    builder->CreateBr(id2bb[1]);

// 1:                                                ; preds = %11, %0
//   %2 = phi i64 [ 0, %0 ], [ %12, %11 ]
//   %3 = trunc i64 %2 to i32
//   br label %4
    builder->SetInsertPoint(id2bb[1]);
    auto&& phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[0]);
    phiNode->addIncoming(id2value[12], id2bb[11]);
    id2value[2] = phiNode;
    id2value[3] = builder->CreateTrunc(id2value[2], builder->getInt32Ty());
    builder->CreateBr(id2bb[4]);

// 4:                                                ; preds = %14, %1
//   %5 = phi i64 [ 0, %1 ], [ %16, %14 ]
//   %6 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 1
//   %7 = load i32, i32* %6, align 4, !tbaa !2
//   %8 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 2
//   %9 = load i32, i32* %8, align 4, !tbaa !7
//   %10 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 0
//   br label %18

    builder->SetInsertPoint(id2bb[4]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[1]);
    phiNode->addIncoming(id2value[16], id2bb[14]);
    id2value[5] = phiNode;

    auto&& pixels = module->getGlobalVariable("pixels");
    id2value[6] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[7] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[8] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[9] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[10] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 0)
        }
    );
    builder->CreateBr(id2bb[18]);



//     11:                                               ; preds = %14
//   %12 = add nuw nsw i64 %2, 1
//   %13 = icmp eq i64 %12, 800
//   br i1 %13, label %39, label %1


    builder->SetInsertPoint(id2bb[11]);
    id2value[12] = builder->CreateNSWAdd(id2value[2], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[13] = builder->CreateICmpEQ(id2value[12], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[13], id2bb[39], id2bb[1]);

// 14:                                               ; preds = %33
//   %15 = trunc i64 %5 to i32
//   store i32 %15, i32* %6, align 4, !tbaa !2
//   store i32 %3, i32* %8, align 4, !tbaa !7
//   %16 = add nuw nsw i64 %5, 1
//   %17 = icmp eq i64 %16, 800
//   br i1 %17, label %11, label %4

    builder->SetInsertPoint(id2bb[14]);
    id2value[15] = builder->CreateTrunc(id2value[5], builder->getInt32Ty());
    builder->CreateStore(id2value[15], id2value[6]);
    builder->CreateStore(id2value[3], id2value[8]);
    id2value[16] = builder->CreateNSWAdd(id2value[5], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[17] = builder->CreateICmpEQ(id2value[16], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[17], id2bb[11], id2bb[4]);



// 18:                                               ; preds = %33, %4
//   %19 = phi i64 [ 0, %4 ], [ %35, %33 ]
//   %20 = phi i32 [ 1000000000, %4 ], [ %34, %33 ]
//   %21 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 1
//   %22 = load i32, i32* %21, align 4, !tbaa !2
//   %23 = sub nsw i32 %22, %7
//   %24 = mul nsw i32 %23, %23
//   %25 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 2
//   %26 = load i32, i32* %25, align 4, !tbaa !7
//   %27 = sub nsw i32 %26, %9
//   %28 = mul nsw i32 %27, %27
//   %29 = add nuw nsw i32 %28, %24
//   %30 = icmp slt i32 %29, %20
//   br i1 %30, label %31, label %33


    builder->SetInsertPoint(id2bb[18]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[4]);
    phiNode->addIncoming(id2value[35], id2bb[33]);
    id2value[19] = phiNode;

    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 1000000000), id2bb[4]);
    phiNode->addIncoming(id2value[34], id2bb[33]);
    id2value[20] = phiNode;
    auto&& points = module->getGlobalVariable("points");
    id2value[21] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[22] = builder->CreateLoad(builder->getInt32Ty(), id2value[21]);
    id2value[23] = builder->CreateNSWSub(id2value[22], id2value[7]);
    id2value[24] = builder->CreateNSWMul(id2value[23], id2value[23]);
    id2value[25] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[26] = builder->CreateLoad(builder->getInt32Ty(), id2value[25]);
    id2value[27] = builder->CreateNSWSub(id2value[26], id2value[9]);
    id2value[28] = builder->CreateNSWMul(id2value[27], id2value[27]);
    id2value[29] = builder->CreateNSWAdd(id2value[28], id2value[24]);
    id2value[30] = builder->CreateICmpSLT(id2value[29], id2value[20]);
    builder->CreateCondBr(id2value[30], id2bb[31], id2bb[33]);

// 31:                                               ; preds = %18
//   %32 = trunc i64 %19 to i32
//   store i32 %32, i32* %10, align 4, !tbaa !8
//   br label %33


    builder->SetInsertPoint(id2bb[31]);
    id2value[32] = builder->CreateTrunc(id2value[19], builder->getInt32Ty());
    builder->CreateStore(id2value[32], id2value[10]);
    builder->CreateBr(id2bb[33]);

// 33:                                               ; preds = %31, %18
//   %34 = phi i32 [ %29, %31 ], [ %20, %18 ]
//   %35 = add nuw nsw i64 %19, 1
//   %36 = icmp ult i64 %19, 9
//   %37 = icmp sgt i32 %34, 0
//   %38 = and i1 %36, %37
//   br i1 %38, label %18, label %14

    builder->SetInsertPoint(id2bb[33]);
    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(id2value[29], id2bb[31]);
    phiNode->addIncoming(id2value[20], id2bb[18]);
    id2value[34] = phiNode;
    id2value[35] = builder->CreateNSWAdd(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[36] = builder->CreateICmpULT(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 9));
    id2value[37] = builder->CreateICmpSGT(id2value[34], llvm::ConstantInt::get(builder->getInt64Ty(), 0));
    id2value[38] = builder->CreateAnd(id2value[36], id2value[37]);
        builder->CreateCondBr(id2value[38], id2bb[18], id2bb[14]);

// 39:                                               ; preds = %11
//   tail call void (...) @gl_start() #7
//   br label %40

    builder->SetInsertPoint(id2bb[39]);
    auto gl_startFunc = module->getFunction("gl_start");
    builder->CreateCall(gl_startFunc->getFunctionType(), gl_startFunc);
    builder->CreateBr(id2bb[40]);
// 40:                                               ; preds = %43, %39
//   %41 = phi i64 [ 0, %39 ], [ %44, %43 ]
//   br label %46

    builder->SetInsertPoint(id2bb[40]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[39]);
    phiNode->addIncoming(id2value[44], id2bb[43]);
    id2value[34] = phiNode;
    builder->CreateBr(id2bb[46]);

// 42:                                               ; preds = %43
//   tail call void (...) @gl_flush() #7
//   ret void

    builder->SetInsertPoint(id2bb[42]);
    auto gl_flushFunc = module->getFunction("gl_flush");
    builder->CreateCall(gl_flushFunc->getFunctionType(), gl_flushFunc);
    builder->CreateRetVoid();
// 43:                                               ; preds = %46
//   %44 = add nuw nsw i64 %41, 1
//   %45 = icmp eq i64 %44, 800
//   br i1 %45, label %42, label %40
    builder->SetInsertPoint(id2bb[43]);
    id2value[44] = builder->CreateNSWAdd(id2value[41], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[45] = builder->CreateICmpEQ(id2value[44], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[45], id2bb[42], id2bb[40]);
// 46:                                               ; preds = %46, %40
//   %47 = phi i64 [ 0, %40 ], [ %49, %46 ]
//   %48 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %41, i64 %47
//   tail call void @gl_put_pixel(%struct.Point* nonnull %48) #7
//   %49 = add nuw nsw i64 %47, 1
//   %50 = icmp eq i64 %49, 800
//   br i1 %50, label %43, label %46

 builder->SetInsertPoint(id2bb[46]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[40]);
    phiNode->addIncoming(id2value[49], id2bb[46]);
    id2value[47] = phiNode;

    pixels = module->getGlobalVariable("pixels");
    id2value[48] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[41],
            id2value[47],
        }
    );
    auto gl_put_pixelFunc = module->getFunction("gl_put_pixel");
    builder->CreateCall(gl_put_pixelFunc->getFunctionType(), gl_put_pixelFunc);
    id2value[49] = builder->CreateNSWAdd(id2value[47], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[50] = builder->CreateICmpEQ(id2value[49], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[50], id2bb[43], id2bb[46]);

}





void reset_picture_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;

    auto&& reset_pictureFunc = module->getFunction("reset_picture");
    id2bb[1] = llvm::BasicBlock::Create(module->getContext(), "1", reset_pictureFunc );
    id2bb[4] = llvm::BasicBlock::Create(module->getContext(), "4", reset_pictureFunc );
    id2bb[11] = llvm::BasicBlock::Create(module->getContext(), "11", reset_pictureFunc );
    id2bb[14] = llvm::BasicBlock::Create(module->getContext(), "14", reset_pictureFunc );
    id2bb[18] = llvm::BasicBlock::Create(module->getContext(), "18", reset_pictureFunc );
    id2bb[31] = llvm::BasicBlock::Create(module->getContext(), "31", reset_pictureFunc );
    id2bb[33] = llvm::BasicBlock::Create(module->getContext(), "33", reset_pictureFunc );
    id2bb[39] = llvm::BasicBlock::Create(module->getContext(), "39", reset_pictureFunc );
    id2bb[40] = llvm::BasicBlock::Create(module->getContext(), "40", reset_pictureFunc );

    //br label %40
    builder->CreateBr(id2bb[40]);


    // 1:                                                ; preds = %40, %11
    //   %2 = phi i64 [ %12, %11 ], [ 0, %40 ]
    //   %3 = trunc i64 %2 to i32
    //   br label %4
    builder->SetInsertPoint(id2bb[1]);
    auto&& phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(id2value[12], id2bb[11]);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[40]);
    id2value[2] = phiNode;
    id2value[3] = builder->CreateTrunc(id2value[2], builder->getInt32Ty());
    builder->CreateBr(id2bb[4]);


// 4:                                                ; preds = %14, %1
//   %5 = phi i64 [ 0, %1 ], [ %16, %14 ]
//   %6 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 1
//   %7 = load i32, i32* %6, align 4, !tbaa !2
//   %8 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 2
//   %9 = load i32, i32* %8, align 4, !tbaa !7
//   %10 = getelementptr inbounds [800 x [800 x %struct.Point]], [800 x [800 x %struct.Point]]* @pixels, i64 0, i64 %2, i64 %5, i32 0
//   br label %18

    builder->SetInsertPoint(id2bb[4]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[1]);
    phiNode->addIncoming(id2value[0], id2bb[14]);
    id2value[5] = phiNode;

    auto&& pixels = module->getGlobalVariable("pixels");
    id2value[6] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[7] = builder->CreateLoad(builder->getInt32Ty(), id2value[6]);
    id2value[8] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[9] = builder->CreateLoad(builder->getInt32Ty(), id2value[8]);
    id2value[10] = builder->CreateGEP(
        pixels->getValueType(),
        pixels,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[2],
            id2value[5],
            llvm::ConstantInt::get(builder->getInt32Ty(), 0)
        }
    );
    builder->CreateBr(id2bb[18]);

// 11:                                               ; preds = %14
//   %12 = add nuw nsw i64 %2, 1
//   %13 = icmp eq i64 %12, 800
//   br i1 %13, label %39, label %1

    builder->SetInsertPoint(id2bb[11]);
    id2value[12] = builder->CreateNSWAdd(id2value[2], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[13] = builder->CreateICmpEQ(id2value[12], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[13], id2bb[39], id2bb[1]);

// 14:                                               ; preds = %33
//   %15 = trunc i64 %5 to i32
//   store i32 %15, i32* %6, align 4, !tbaa !2
//   store i32 %3, i32* %8, align 4, !tbaa !7
//   %16 = add nuw nsw i64 %5, 1
//   %17 = icmp eq i64 %16, 800
//   br i1 %17, label %11, label %4


    builder->SetInsertPoint(id2bb[14]);
    id2value[15] = builder->CreateTrunc(id2value[5], builder->getInt32Ty());
    builder->CreateStore(id2value[15], id2value[6]);
    builder->CreateStore(id2value[3], id2value[8]);
    id2value[16] = builder->CreateNSWAdd(id2value[5], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[17] = builder->CreateICmpEQ(id2value[16], llvm::ConstantInt::get(builder->getInt64Ty(), 800));
    builder->CreateCondBr(id2value[17], id2bb[11], id2bb[4]);

// 18:                                               ; preds = %33, %4
//   %19 = phi i64 [ 0, %4 ], [ %35, %33 ]
//   %20 = phi i32 [ 1000000000, %4 ], [ %34, %33 ]
//   %21 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 1
//   %22 = load i32, i32* %21, align 4, !tbaa !2
//   %23 = sub nsw i32 %22, %7
//   %24 = mul nsw i32 %23, %23
//   %25 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %19, i32 2
//   %26 = load i32, i32* %25, align 4, !tbaa !7
//   %27 = sub nsw i32 %26, %9
//   %28 = mul nsw i32 %27, %27
//   %29 = add nuw nsw i32 %28, %24
//   %30 = icmp slt i32 %29, %20
//   br i1 %30, label %31, label %33

    builder->SetInsertPoint(id2bb[18]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[4]);
    phiNode->addIncoming(id2value[35], id2bb[33]);
    id2value[19] = phiNode;

    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 1000000000), id2bb[4]);
    phiNode->addIncoming(id2value[34], id2bb[33]);
    id2value[20] = phiNode;
    auto&& points = module->getGlobalVariable("points");
    id2value[21] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    id2value[22] = builder->CreateLoad(builder->getInt32Ty(), id2value[21]);
    id2value[23] = builder->CreateNSWSub(id2value[22], id2value[7]);
    id2value[24] = builder->CreateNSWMul(id2value[23], id2value[23]);
    id2value[25] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[19],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    id2value[26] = builder->CreateLoad(builder->getInt32Ty(), id2value[25]);
    id2value[27] = builder->CreateNSWSub(id2value[26], id2value[9]);
    id2value[28] = builder->CreateNSWMul(id2value[27], id2value[27]);
    id2value[29] = builder->CreateNSWAdd(id2value[28], id2value[24]);
    id2value[30] = builder->CreateICmpSLT(id2value[29], id2value[20]);
    builder->CreateCondBr(id2value[30], id2bb[31], id2bb[33]);


// 31:                                               ; preds = %18
//   %32 = trunc i64 %19 to i32
//   store i32 %32, i32* %10, align 4, !tbaa !8
//   br label %33

    builder->SetInsertPoint(id2bb[31]);
    id2value[32] = builder->CreateTrunc(id2value[19], builder->getInt32Ty());
    builder->CreateStore(id2value[32], id2value[10]);
    builder->CreateBr(id2bb[33]);

// 33:                                               ; preds = %31, %18
//   %34 = phi i32 [ %29, %31 ], [ %20, %18 ]
//   %35 = add nuw nsw i64 %19, 1
//   %36 = icmp ult i64 %19, 9
//   %37 = icmp sgt i32 %34, 0
//   %38 = and i1 %36, %37
//   br i1 %38, label %18, label %14

    builder->SetInsertPoint(id2bb[33]);
    phiNode = builder->CreatePHI(builder->getInt32Ty(), 2);
    phiNode->addIncoming(id2value[29], id2bb[31]);
    phiNode->addIncoming(id2value[20], id2bb[18]);
    id2value[34] = phiNode;
    id2value[35] = builder->CreateNSWAdd(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 1));
    id2value[36] = builder->CreateICmpULT(id2value[19], llvm::ConstantInt::get(builder->getInt64Ty(), 9));
    id2value[37] = builder->CreateICmpSGT(id2value[34], llvm::ConstantInt::get(builder->getInt64Ty(), 0));
    id2value[38] = builder->CreateAnd(id2value[36], id2value[37]);
        builder->CreateCondBr(id2value[38], id2bb[18], id2bb[14]);

// 39:                                               ; preds = %11
//   store i1 false, i1* @flag_no_recalc, align 4
//   ret void
    builder->SetInsertPoint(id2bb[39]);
    auto flag_no_recalc = module->getGlobalVariable("flag_no_recalc");
    builder->CreateStore(llvm::ConstantInt::get(builder->getInt32Ty(), false), flag_no_recalc);

// 40:                                               ; preds = %40, %0
//   %41 = phi i64 [ 0, %0 ], [ %48, %40 ]
//   %42 = tail call i32 (...) @int_rand() #5
//   %43 = srem i32 %42, 800
//   %44 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %41, i32 1
//   store i32 %43, i32* %44, align 4, !tbaa !2
//   %45 = tail call i32 (...) @int_rand() #5
//   %46 = srem i32 %45, 800
//   %47 = getelementptr inbounds [10 x %struct.Point], [10 x %struct.Point]* @points, i64 0, i64 %41, i32 2
//   store i32 %46, i32* %47, align 4, !tbaa !7
//   %48 = add nuw nsw i64 %41, 1
//   %49 = icmp eq i64 %48, 10
//   br i1 %49, label %1, label %40

    builder->SetInsertPoint(id2bb[40]);
    phiNode = builder->CreatePHI(builder->getInt64Ty(), 2);
    phiNode->addIncoming(llvm::ConstantInt::get(builder->getInt64Ty(), 0), id2bb[0]);
    phiNode->addIncoming(id2bb[48], id2bb[40]);
    id2value[41] = phiNode;

    auto int_randFunc = module->getFunction("int_rand");
    id2value[42] = builder->CreateCall(
        int_randFunc->getFunctionType(),
        int_randFunc,
        {});
        id2value[43] = builder->CreateSRem(id2value[42], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    points = module->getGlobalVariable("points");
    id2value[44] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[41],
            llvm::ConstantInt::get(builder->getInt32Ty(), 1)
        }
    );
    builder->CreateStore(id2value[43], id2value[44]);


id2value[45] = builder->CreateCall(
        int_randFunc->getFunctionType(),
        int_randFunc,
        {});
        id2value[46] = builder->CreateSRem(id2value[45], llvm::ConstantInt::get(builder->getInt32Ty(), 800));
    id2value[47] = builder->CreateGEP(
        points->getValueType(),
        points,
        {        
            llvm::ConstantInt::get(builder->getInt64Ty(), 0),
            id2value[41],
            llvm::ConstantInt::get(builder->getInt32Ty(), 2)
        }
    );
    builder->CreateStore(id2value[46], id2value[47]);
    id2value[48] = builder->CreateNSWAdd(id2value[41], llvm::ConstantInt::get(builder->getInt32Ty(), 1));
    id2value[49] = builder->CreateICmpEQ(id2value[48], llvm::ConstantInt::get(builder->getInt32Ty(), 10));
    builder->CreateCondBr(id2value[49], id2bb[1], id2bb[40]);
}

void main_codegen(llvm::Module* module, llvm::IRBuilder<>* builder) {
    auto mainFunc = module->getFunction("main");
    llvm::BasicBlock *entry = llvm::BasicBlock::Create(module->getContext(), "entrypoint", mainFunc);
    builder->SetInsertPoint(entry);

//   tail call void @gl_init(i32 %0, i8** %1) #7
//   tail call void @reset_picture()
//   tail call void @display() #7
//   %3 = load i1, i1* @show_window, align 4
//   br i1 %3, label %6, label %4
    std::cout << "bef all calls" << std::endl;

    auto gl_initFunc = module->getFunction("gl_init");
    builder->CreateCall(gl_initFunc->getFunctionType(), gl_initFunc);

    auto reset_pictureFunc = module->getFunction("reset_picture");
    builder->CreateCall(reset_pictureFunc->getFunctionType(), reset_pictureFunc);
    
    auto displayFunc = module->getFunction("display");
    builder->CreateCall(reset_pictureFunc->getFunctionType(), displayFunc);
    std::cout << "aft all calls" << std::endl;

    std::unordered_map<int, llvm::BasicBlock*> id2bb;
    std::unordered_map<int, llvm::Value*> id2value;
    id2bb[4] = llvm::BasicBlock::Create(module->getContext(), "4", mainFunc);
    id2bb[6] = llvm::BasicBlock::Create(module->getContext(), "6", mainFunc);
    std::cout << "aft labels" << std::endl;


//     4:                                                ; preds = %2, %4
//   tail call void @timf(i32 10) #7
//   %5 = load i1, i1* @show_window, align 4
//   br i1 %5, label %6, label %4
    builder->SetInsertPoint(id2bb[4]);
    auto timfFunc = module->getFunction("timf");
    builder->CreateCall(timfFunc->getFunctionType(), timfFunc);
    auto show_window = module->getGlobalVariable("show_window");
    id2value[5] = builder->CreateLoad(builder->getInt1Ty(), show_window);
    std::cout << "aft 1block" << std::endl;


// 6:                                                ; preds = %4, %2
//   ret i32 0
    builder->SetInsertPoint(id2bb[6]);
builder->CreateRet(llvm::ConstantInt::get(builder->getInt32Ty(), 9));


}

void create_declarations(llvm::Module* module, llvm::IRBuilder<>* builder) {
    // declare void @main()
    llvm::FunctionType *funcType = 
        llvm::FunctionType::get(builder->getVoidTy(), false);

    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "LLVM_main", module);
    llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "reset_picture", module);
}

int main() {

    llvm::LLVMContext context;
    // ; ModuleID = 'top'
    // source_filename = "top"
    llvm::Module *module = new llvm::Module("top", context);
    llvm::IRBuilder<> builder(context);
    std::cout << "bef declarations" << std::endl;
    create_declarations(module, &builder);
    std::cout << "aft declarations" << std::endl;

    // declare void @main()
    // llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    // llvm::Function *mainFunc = llvm::Function::Create(
    // funcType, llvm::Function::ExternalLinkage, "main", module);

    // entrypoint:


    // Simple Run LLVM_main
    // llvm::Function *CalleeF = llvm::Function::Create(llvm::FunctionType::get(builder.getVoidTy(), llvm::ArrayRef<llvm::Type *>(builder.getVoidTy()), false), llvm::Function::ExternalLinkage, "LLVM_main", module);
    // builder.CreateCall(CalleeF);
    std::cout << "bef maincodegen" << std::endl;

    main_codegen(module, &builder);
    std::cout << "aft maincodegen" << std::endl;

    // call @init_world

    reset_picture_codegen(module, &builder);
    display_codegen(module, &builder);
    dump_codegen(module);

    //Interpreter of LLVM IR
//     llvm::ExecutionEngine *ee =
//         llvm::EngineBuilder(std::unique_ptr<llvm::Module>(module)).create();

//           ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void *
//                                  {
//     if (fnName == "LLVM_main") {
//       return reinterpret_cast<void *>(LLVM_main);
//     }
//     return nullptr; });

//   ee->finalizeObject();
//   std::vector<llvm::GenericValue> noargs;
//   llvm::GenericValue v = ee->runFunction(mainFunc, noargs);


    return 0;
}