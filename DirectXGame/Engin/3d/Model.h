#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <DirectXMath.h>
#include <DirectXTex.h>

// �m�[�h
struct Node
{
	// ���O
	std::string name;
	// ���[�J���X�P�[��
	DirectX::XMVECTOR scaling = { 1,1,1,0 };
	// ���[�J����]�p
	DirectX::XMVECTOR rotation = { 0,0,0,0 };
	// ���[�J���ړ�
	DirectX::XMVECTOR translation = { 0,0,0,1 };
	// ���[�J���ό`�s��
	DirectX::XMMATRIX transform;
	// �O���[�o���ό`�s��
	DirectX::XMMATRIX globalTransform;
	// �e�m�[�h
	Node* parent = nullptr;
};

class Model {

public:
	//�t�����h�N���X
	friend class FbxLoader;

	struct VertexPosNormalUv {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};

	// �o�b�t�@����
	void CreateBuffers(ID3D12Device* device);
	// �`��
	void Draw(ID3D12GraphicsCommandList* cmdList);

private:
	//���f����
	std::string name;
	//�m�[�h�z��
	std::vector<Node> nodes;
	//���b�V�������m�[�h 
	Node* meshNode = nullptr;
	//���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	//���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	// �A���r�G���g�W��
	DirectX::XMFLOAT3 ambient = { 1,1,1 };
	// �f�B�t���[�Y�W��
	DirectX::XMFLOAT3 diffuse = { 1,1,1 };
	// �e�N�X�`�����^�f�[�^
	DirectX::TexMetadata metadata = {};
	// �X�N���b�`�C���[�W
	DirectX::ScratchImage scratchImg = {};
};