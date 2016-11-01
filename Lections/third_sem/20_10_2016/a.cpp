Namespaces
using декларации:
В GNOME функции называются gnome_panel_applet_indicator_create(); Чтобы не было коллизий. Для того, чтобы не было таких длинных названий можно использовать namespace
namespace gnome
{
	namespace panel
	{
		namespace applet_indicator
		{
			void create();
		}
	}
}

Вызов: gnome::panel::apllet_indicator::creat(); Больше текста, но зато внутри applet_indicator можно вызывать без разыменовывания
Поиск происходит снизу вверх (сначала в applet_indicator, потом в panel и так далее)
Так же ищется когда a::b::c поднимается наверх пока не найдет namespace a
Если хотим начать искать функции из глобального namespace пишем ::f()

Можно делать алиасы. namespace fs=gnome

namespace n
{
	void f();
}

Если постоянно юзается f чтобы не писать постоянно разыменовывание можно написать using n::f; Это работает так, как будто в данном месте (строке) объявлена функция.
Если объявить функцию с таким же именем то это будет перегрузкой.
Работает и в классах:
struct base
{
	void f();
};
struct base2
{
	void f();
}
struct derived:base, base2
{
	using base::f;
}

using директивы:
using namespace n;

Это значит, что функции (или не функции) будут искаться не только в верхнем скоупе, но и в n

namespace std
{
	void f(int);
}

using namespace std;
void f(float);

int main()
{
	f(5); -- вызывается int
	::f(5); -- вызывается float, так как иначе функцию из класса нельзя было бы юзать

}

a::b::c -- первая часть имени неквалифицированный, остальные квалифицированный
неквалифицированный -- поиск неймспейса a
квалифицированный -- поиск там, куда сослася неквалифицированный, а потом ищем дальше. Поэтому в main такая хрень


Argument-Dependent Lookup (ADL)

namespace mylib
{
	struct mytype
	{};
}

mylib::mytype a, b;
a+b; Откуда брать плюс? оператор может быть объявлен снаружи где-то от класса.
Это почти эквивалентно operator+(a, b); А эта запись не найдет оператор внутри namespace
Поэтому функции ищутся не только в глобальном нэймспейс, но и в тех, где лежат аргументы функции (это справедливо для всех функций)
Ищет только в namespace, не поднимаясь наверх и не заглядывая в using namespace. 

Пример использования ADL -- swap.
template <typename T>
void f(T& a, T& b)
{
	Для своих типов писать swap а не std::swap так как обычно swap пишется для своих классов свой.
	Надо делать так:
	using std::swap;
	swap(a, b); Так подберется нужный своп.
}


В хедерах нельзя писать using, так как иначе он будет using везде где инклудится

Анонимные namespace

//a.cpp
struct x
{
	int a;
};

std::vector<x> v;

//b.cpp
struct x
{
	char a;
};

std::vector<x> u;

// не сработает -- один и тот же код для по сути разных векторов

Для того чтобы работало класс можно погрузить в namespace:
namespace
{
	struct x...
}
Работает это как namespace с каким-то именем а после этого написан using namespace какое-то имя.

































