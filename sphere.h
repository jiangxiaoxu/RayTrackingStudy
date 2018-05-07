﻿#pragma once
#include "hitable.h"
class sphere :	public hitable
{
public:
	sphere(){}
	sphere(vec3 cen, double r) :center(cen),radius(r){}
	virtual bool hit(const ray& r, double tmin, double tmax,hit_record& rec) const;
	vec3 center;
	double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = 2.0*dot(oc, r.direction());
	double c = dot(oc, oc) - radius*radius;
	double discriminant = b*b - 4.0 * a*c;
	if (discriminant > 0) {
		//原作者这里的代码有问题
		double temp = (-b - sqrt(discriminant)) / (2.0*a);
		if (temp<t_max && temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		temp= (-b + sqrt(discriminant)) / (2.0*a);
		if (temp<t_max && temp>t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}