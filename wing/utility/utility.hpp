#pragma once

#include<algorithm>


namespace wing{

/**
*@brief 汎用的な便利関数・クラス
*/
namespace utility{


/**
*@brief 上限と下限の範囲内に丸めた値を返す
*@param val 対象となる値
*@param under 下限
*@param upper 上限
*/
template<typename T>
const T& limit(const T& val,const T& under,const T& upper){
	return  std::min<T>(upper, std::max<T>(under, val));
}

/**
*@brief クラスをデコレートした型を返すメタ関数
*@tparam Decoratee デコレートされるクラス
*@tparam Decorator デコレータ
*/
template<class Decoratee, template<class> class Decorator>
struct decorate{
/**
*@brief デコレートされた結果の型
*/
typedef Decorator<Decoratee> Type;
};



}}