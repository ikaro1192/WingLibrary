#pragma once

#include<algorithm>


namespace wing{

/**
*@brief �ėp�I�ȕ֗��֐��E�N���X
*/
namespace utility{


/**
*@brief ����Ɖ����͈͓̔��Ɋۂ߂��l��Ԃ�
*@param val �ΏۂƂȂ�l
*@param under ����
*@param upper ���
*/
template<typename T>
const T& limit(const T& val,const T& under,const T& upper){
	return  std::min<T>(upper, std::max<T>(under, val));
}

/**
*@brief �N���X���f�R���[�g�����^��Ԃ����^�֐�
*@tparam Decoratee �f�R���[�g�����N���X
*@tparam Decorator �f�R���[�^
*/
template<class Decoratee, template<class> class Decorator>
struct decorate{
/**
*@brief �f�R���[�g���ꂽ���ʂ̌^
*/
typedef Decorator<Decoratee> Type;
};



}}