#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix4x4.h"
#include "AABB.h"

const int kRowHeight = 20;
const int kColumnWidth = 60;


#pragma region Vectror3
// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);
// 積
Vector3 Multiply(const Vector3& v1, const Vector3& v2);
// 内積
float Dot(const Vector3& v1, const Vector3& v2);
// 長さ（ノルム）
float Length(const Vector3& v);
// 正規化
Vector3 Normalize(const Vector3& v);
// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);
// 背面カリング
bool IsFront(const Vector3& v1, const Vector3 obj[3]);
// 正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2);
// 最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

#pragma endregion

#pragma region Matrix4x4

Matrix4x4 operator*(const Matrix4x4& num1, const Matrix4x4& num2);

// 加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
// 減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// 行列式
float Det(Matrix4x4 matrix);
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
// 単位行列の作成
Matrix4x4 MakeIdentity4x4();
// 回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateXYZMatrix(const Matrix4x4& matrixX, const Matrix4x4& matrixY, const Matrix4x4& matrixZ);

Matrix4x4 MakeRotateMatrix(const Vector3& rotate);

Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);

// アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
// ベクトル変換
Vector3 Transform(const Vector3& v, const Matrix4x4& m);
// 1. 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRation, float nearClip, float farClip);
// 2. 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
// 3. ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);


#pragma endregion

// minとmaxが入れ替わらないように
void ControlMinMax(AABB& a);
// AABB同士の衝突判定
bool IsCollision(const AABB& a, const AABB& b);

// 小さいほうを返す
float Min(float num, float min);
// 大きいほうを返す
float Max(float num, float max);

float Clamp(float num, float hight, float low);