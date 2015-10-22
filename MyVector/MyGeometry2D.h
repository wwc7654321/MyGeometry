#ifndef MYGEOMETRY2D_H
#define MYGEOMETRY2D_H
#include <math.h>
namespace MyGeo2D{

	template<typename VT = int, VT INVALIDVT = -1>
	class Point2D;
	template<typename VT = int, VT INVALIDVT = -1>
	class Line2D;
	template<typename VT = int, VT INVALIDVT = -1>
	class Vector2D;


#ifndef MYABS
#define MYABS(x) ((x)<(-x)?(-x):(x))
#endif
	template<typename VT, VT INVALIDVT >
	class Point2D
	{
	public:
		Point2D() :x(0), y(0), invalid(true){} 
		explicit Point2D(const Vector2D<VT,INVALIDVT>& a) :x(a.x),y(a.y){}
		Point2D(VT xx,VT yy) :x(xx), y(yy), invalid(false){}
		// �㵽�����
		VT Dist(const Point2D<VT,INVALIDVT> & point) const { return Line2D<VT,INVALIDVT>(*this,point).Length(); }
		// �㵽�߾���
		VT Dist(const Line2D<VT,INVALIDVT>& line) const{ 
			// ��ά������˳��ȿɿ���������Ϊ�������ߵ�ƽ���ı������
			// ������ױ߳����ڵױ��ϵĸߣ����㵽ֱ�߾���
			if (!IsValid() || !line.IsValid()) return INVALIDVT;
			const Vector2D<VT,INVALIDVT> v = line.ToVector(),
				u(line.P1(), *this); 
			return v.CrossLength(u) / v.Length();
		}
		Point2D<VT,INVALIDVT>  operator+ (const Point2D<VT,INVALIDVT> &a)const { Point2D<VT,INVALIDVT> tmp(*this); tmp += a; return tmp; }
		Point2D<VT,INVALIDVT> & operator+=(const Point2D<VT,INVALIDVT> &a) { x += a.x; y += a.y; invalid = false; return *this; }
		Point2D<VT,INVALIDVT>  operator- (const Point2D<VT,INVALIDVT> &a)const { Point2D<VT,INVALIDVT> tmp(*this); tmp -= a; return tmp; }
		Point2D<VT,INVALIDVT> & operator-=(const Point2D<VT,INVALIDVT> &a) { x -= a.x; y -= a.y; invalid = false; return *this; }
//		Point2D<VT,INVALIDVT> & operator* (const Point2D<VT,INVALIDVT> &a)const { Point2D<VT,INVALIDVT> tmp(this); tmp *= a; return tmp; }
//		Point2D<VT,INVALIDVT> & operator*=(const Point2D<VT,INVALIDVT> &a) { x *= a.x; y *= a.y; invalid = false; return *this; }
//		Point2D<VT,INVALIDVT> & operator/ (const Point2D<VT,INVALIDVT> &a)const { Point2D<VT,INVALIDVT> tmp(this); tmp /= a; return tmp; }
//		Point2D<VT,INVALIDVT> & operator/=(const Point2D<VT,INVALIDVT> &a) { x /= a.x; y /= a.y; invalid = false; return *this; }

		Point2D<VT,INVALIDVT>  operator* (VT a)const { Point2D<VT,INVALIDVT> tmp(*this); tmp *= a; return tmp; }
		Point2D<VT,INVALIDVT> & operator*=(VT a) { x *= a; y *= a; invalid = false; return *this; }
		Point2D<VT,INVALIDVT>  operator/ (VT a)const { Point2D<VT,INVALIDVT> tmp(*this); tmp /= a; return tmp; }
		Point2D<VT,INVALIDVT> & operator/=(VT a) { x /= a; y /= a; invalid = false; return *this; }
		bool operator==(const Point2D<VT,INVALIDVT> &a)const { return x == a.x&&y == a.y; }
		bool operator!=(const Point2D<VT,INVALIDVT> &a)const { return x != a.x||y != a.y; }

		Point2D<VT,INVALIDVT> & operator=(const Point2D<VT,INVALIDVT> &a) { Set(a); return *this; }
		void Set(const Point2D<VT,INVALIDVT> &a) { x = a.x; y = a.y; invalid = a.invalid; }
		void Set(VT xx, VT yy) { x = xx; y = yy; invalid = false;} 
		VT X()const {  return x; }
		VT Y()const {  return y; }
		VT X(VT xx) { invalid = false; return x = xx; }
		VT Y(VT yy) { invalid = false; return y = yy; }
		bool IsValid() const{ return !invalid; }
		void SetZero() { x = 0; y = 0; invalid = false; }
		bool IsZero() { return x == 0 && y == 0; }
	protected: 
		Point2D<VT,INVALIDVT> & operator=(const Vector2D<VT,INVALIDVT> &a);	// ��ֹVector��Point֮����ʽת��
		friend class Line2D<VT,INVALIDVT>;
		VT x;
		VT y;
		bool invalid;
	};

	template<typename VT, VT INVALIDVT>
	class Vector2D :public Point2D<VT,INVALIDVT> {
	public:
		Vector2D() :Point2D() {}
		explicit Vector2D(const Point2D<VT,INVALIDVT>& point) :Point2D(point) {} // ��ֹVector��Point֮����ʽת��
		Vector2D(const Point2D<VT,INVALIDVT>& point1, const Point2D<VT,INVALIDVT>& point2) :Point2D(point2-point1) {}
		Vector2D(VT xx, VT yy) :Point2D(xx,yy) {}
		// ������
		VT operator* (const Vector2D<VT,INVALIDVT> &a)const { return a.x*x + a.y*y; }
		Vector2D<VT, INVALIDVT>  operator+ (const Vector2D<VT, INVALIDVT> &a)const { Vector2D<VT, INVALIDVT> tmp(*this); tmp += a; return tmp; }
		Vector2D<VT, INVALIDVT> & operator+=(const Vector2D<VT, INVALIDVT> &a) { Point2D<VT, INVALIDVT>::operator+=(a); return *this; }
		Vector2D<VT, INVALIDVT>  operator- (const Vector2D<VT, INVALIDVT> &a)const { Vector2D<VT, INVALIDVT> tmp(*this); tmp -= a; return tmp; }
		Vector2D<VT, INVALIDVT> & operator-=(const Vector2D<VT, INVALIDVT> &a) { Point2D<VT, INVALIDVT>::operator-=(a); return *this; }

		Vector2D<VT, INVALIDVT>  operator* (VT a)const { Vector2D<VT, INVALIDVT> tmp(*this); tmp *= a; return tmp; }
		Vector2D<VT, INVALIDVT> & operator*=(VT a) { Point2D<VT, INVALIDVT>::operator*=(a); return *this; }
		Vector2D<VT, INVALIDVT>  operator/ (VT a)const { Vector2D<VT, INVALIDVT> tmp(*this); tmp /= a; return tmp; }
		Vector2D<VT, INVALIDVT> & operator/=(VT a) { Point2D<VT, INVALIDVT>::operator/=(a); return *this; }
		// ���
		Vector2D<VT,INVALIDVT> Cross(const Vector2D<VT,INVALIDVT>& a)const { return Vector2D<VT,INVALIDVT>(); }
		// ��˽���ĳ���
		VT CrossLength(const Vector2D<VT,INVALIDVT>& a)const { VT b = x*a.y - y*a.x; return MYABS(b); }
		// ��������
		VT Length()const { return (VT)sqrt(x*x+y*y); }
		// ��˲�����
		Vector2D<VT,INVALIDVT> & CrossAndSet(const Vector2D<VT,INVALIDVT>& a) { return *this = Vector2D<VT,INVALIDVT>(); }
		// ƽ��   parallel 
		bool Parallel(const Vector2D<VT,INVALIDVT>&a)const { return x*a.y == y*a.x; }
		// ��ֱ   perpendicular
		bool Perp(const Vector2D<VT,INVALIDVT>&a)const { return 0==*this * a; }
		// ���
		void Normalize() { operator /=(Length()); }
		// ��õ�λ����
		Vector2D<VT, INVALIDVT> ToNormalized() { return *this / Length(); }
		// ͶӰ���ȣ�����С��0
		VT ProjectLength(const Vector2D<VT, INVALIDVT>& obj) { return *this * obj / Length(); }
		// ͶӰ����
		Vector2D<VT, INVALIDVT> ProjectVector(const Vector2D<VT, INVALIDVT>& obj)
		{
			VT i = (operator * (obj)) / (x*x + y*y );
			return Vector2D<VT, INVALIDVT>(x*i, y*i);
		}
	};

	template<typename VT=int, VT INVALIDVT >
	class Line2D
	{
	public:
		Line2D() :p1(), p2(){}
		explicit Line2D(const Point2D<VT,INVALIDVT>& point) :p1(0,0), p2(point){}
		Line2D(const Point2D<VT,INVALIDVT>& point1, const Point2D<VT,INVALIDVT>& point2) :p1(point1), p2(point2){}
		Line2D(VT x1,VT y1,VT x2, VT y2) :p1(x1,y1), p2(x2,y2) {}

		Point2D<VT,INVALIDVT> MidPoint()const { return MidPoint(p1,p2); }
		static Point2D<VT,INVALIDVT> MidPoint(const Point2D<VT,INVALIDVT> & p1, const Point2D<VT,INVALIDVT>& p2) { Point2D<VT,INVALIDVT> tmp(p1); tmp += p2; tmp /= 2; return tmp; }
		VT Dist(const Point2D<VT,INVALIDVT> & p1) const { return p1.Dist(*this); }
		//ƽ��   parallel 
		bool Parallel(const Line2D<VT,INVALIDVT>&a)const { a.ToVector().Parallel(ToVector()); }
		bool Parallel(const Vector2D<VT,INVALIDVT>&a)const { a.Parallel(ToVector()); }
		//��ֱ   perpendicular
		bool Perp(const Line2D<VT,INVALIDVT>&a)const { a.ToVector().Parallel(ToVector()); }
		bool Perp(const Vector2D<VT,INVALIDVT>&a)const { a.Parallel(ToVector()); }
		// ����ֱ����
		bool PointOnLine(const Point2D<VT,INVALIDVT>&a)const { 
			if (!IsValid())return false;
			return DX()* a.y - DY()* a.x == p2.x*p1.y - p1.x*p2.y;
		}
		// �����߶���
		bool PointOnSegLine(const Point2D<VT,INVALIDVT>&a)const { 
			if (!IsValid())return false;
			return (p1.x<p2.x ? p1.x : p2.x) <= a.x && (p1.x>p2.x ? p1.x : p2.x) >= a.x &&
				(p1.y<p2.y ? p1.y : p2.y) <= a.y && (p1.y>p2.y ? p1.y : p2.y) >= a.y &&PointOnLine(a);
		}

		Line2D<VT,INVALIDVT> & operator=(const Line2D<VT,INVALIDVT> &line) { Set(line); return *this; }
		void Set(const Line2D<VT,INVALIDVT>&line) { p1 = line.p1; p2 = line.p2; }
		void Set(const Point2D<VT,INVALIDVT>&point1, const Point2D<VT,INVALIDVT>&point2) { p1 = point1; p2 = point2; }
		void Set(VT x1, VT y1, VT x2, VT y2) { p1.Set(x1, y1); p2.Set(x2, y2); }
		bool operator==(const Line2D<VT,INVALIDVT> &a)const { return (a.p1 == p1 && a.p2 == p2) || (a.p1 == p2 && a.p2 == p1); }
		bool operator!=(const Line2D<VT,INVALIDVT> &a)const { return (a.p1 != p1 || a.p2 != p2) && (a.p1 != p2 || a.p2 != p1); }

		VT Length() const { return sqrt(SqLength()); }
		VT SqLength() const { VT i = (p1.x - p2.x),j=(p1.y-p2.y);	return i*i + j*j;	}
		VT ManhattanLength() const { VT i = (p1.x - p2.x), j = (p1.y - p2.y); return MYABS(i) + MYABS(j);	}
		Point2D<VT,INVALIDVT> P1()const { return p1; }
		Point2D<VT,INVALIDVT> P2()const { return p2; }
		void P1(const Point2D<VT,INVALIDVT>& point) { p1 = point; }
		void P2(const Point2D<VT,INVALIDVT>& point) { p2 = point; }
		VT DX()const { return p2.x-p1.x; }
		VT DY()const { return p2.y -p1.y; }
		bool IsValid() const { return p1.IsValid()&& p2.IsValid()&& p1!=p2; }
		void SetZero() { p1.SetZero(); p2.SetZero(); }
		

		void Move(const Vector2D<VT,INVALIDVT>& a) { p1 += a; p2 += a; }

		Vector2D<VT,INVALIDVT> ToVector()const { return Vector2D<VT,INVALIDVT>(p1 , p2); }
	private: 
		Point2D<VT,INVALIDVT> p1, p2;
	};

	template<typename VT, VT INVALIDVT = -1>
	class Geo2D {
	public:
		typedef VT Vt;
		typedef Point2D<VT, INVALIDVT> Point;
		typedef Vector2D<VT, INVALIDVT> Vector;
		typedef Line2D<VT, INVALIDVT> Line;
	};

};




#ifdef MYGEO_AUTO_DEFINE_2D_TYPE
typedef MYGEO_AUTO_DEFINE_2D_TYPE Vt2D;
typedef MyGeo2D::Geo2D<AUTO_DEFINE_2D_TYPE>::Point Point2D;
typedef MyGeo2D::Geo2D<AUTO_DEFINE_2D_TYPE>::Line Line2D;
typedef MyGeo2D::Geo2D<AUTO_DEFINE_2D_TYPE>::Vector Vector2D;
#endif

#endif // MYGEOMETRY2D