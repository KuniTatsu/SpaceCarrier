//�D�̃p�[�c���Ǘ�����}�l�[�W���N���X
//�V���O���g���ō���Ă���
#pragma once
#include<vector>
#include<list>
#include<string>
#include<unordered_map>
#include"../../dxlib_ext/dxlib_ext.h"
#include<memory>

class PartsBase;
class ShipParts;
class WeaponParts;

class PartsManager {

protected:
	PartsManager();
	~PartsManager();
public:
	//�C���X�^���X���Ȃ���ΐ����A����ΕԂ��֐�
	static PartsManager* Instance();

	//������
	void Init();
	//Csv���[�h
	void LoadCsv();

	//�p�[�c�R�[�h
	enum class PARTSCODE:uint32_t {
		HULL,
		CONTAINER,
		ARMOR,
		GENERATOR,
		THRUSTER,
		MAX
	};
	//�����p�[�c�i�[�֐�
	void SetProtoTypeParts(std::vector<std::shared_ptr<PartsBase>>& PartsSet);
	//��������i�[�֐�
	void SetProtoTypeWeapon(std::vector<std::shared_ptr<PartsBase>>& WeaponSet);

	//�p�[�c�f�[�^�擾�֐�


private:
	//�V���O���g���C���X�^���X
	static PartsManager* instance;

	std::vector<std::vector<std::string>> loadPartsCsv;

	std::vector<std::vector<std::string>> loadWeaponPartsCsv;

	//�D�̃p�[�c�}�X�^�[
	std::vector<std::vector<std::shared_ptr<ShipParts>>>shipPartsMaster;
	//����p�[�c�}�X�^�[
	std::vector<std::vector<std::shared_ptr<WeaponParts>>>weaponPartsMaster;

};