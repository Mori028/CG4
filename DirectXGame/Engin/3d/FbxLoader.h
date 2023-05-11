﻿#pragma once

#include "fbxsdk.h"

#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include "Model.h"

class FbxLoader
{
private://エイリアス
//std::を省略
	using string = std::string;

public://定数
	//モデル格納ルートパス
	static const string baseDirectory;
	// テクスチャがない場合の標準テクスチャファイル名
	static const string defaultTextureFileName;

	/// <summary>
	/// ファイルからFBXモデル読み込み
	/// </summary>	
	void LoadModelFromFile(const string& modelName);

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FbxLoader* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ID3D12Device* device);

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// 再帰的にノード構成を解析 
	/// </summary>
	void ParseNodeRecursive(Model* model, FbxNode* fbxNode,Node* parent = nullptr);

	/// <summary>
	/// メッシュ読み取り
	/// </summary>
	void ParseMesh(Model* model, FbxNode* fbxNode);
	// 頂点座標読み取り
	void ParseMeshVertices(Model* model, FbxMesh* fbxMesh);
	// 面情報読み取り
	void ParseMeshFaces(Model* model, FbxMesh* fbxMesh);
	// マテリアル読み取り
	void ParseMaterial(Model* model, FbxNode* fbxNode);
	// テクスチャ読み込み
	void LoadTexture(Model* model, const std::string& fullpath);
private:
	// privateなコンストラクタ（シングルトンパターン）
	FbxLoader() = default;
	// privateなデストラクタ（シングルトンパターン）
	~FbxLoader() = default;
	// コピーコンストラクタを禁止（シングルトンパターン）
	FbxLoader(const FbxLoader& obj) = delete;
	// コピー代入演算子を禁止（シングルトンパターン）
	void operator=(const FbxLoader& obj) = delete;
	//D3D12デバイス
	ID3D12Device* device = nullptr;
	//FBXマネージャー
	FbxManager* fbxManager = nullptr;
	//FBXインポータ―
	FbxImporter* fbxImporter = nullptr;
	// ディレクトリを含んだファイルパスからファイル名を抽出する
	std::string ExtractFileName(const std::string& path);
};