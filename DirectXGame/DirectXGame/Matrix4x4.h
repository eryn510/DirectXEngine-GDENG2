#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{
		
	}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(float) * 16);

		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setTranslation(const Vector3D &translation)
	{
		m_mat[3][0] = translation.m_x;
		m_mat[3][1] = translation.m_y;
		m_mat[3][2] = translation.m_z;
	}

	void setScale(const Vector3D& scale)
	{
		m_mat[0][0] = scale.m_x;
		m_mat[1][1] = scale.m_y;
		m_mat[2][2] = scale.m_z;
	}

	void setQuaternionRotation(float theta, float x, float y, float z)
	{
		float normU, qx, qy, qz, qw;

		//normalizing axis vector
		normU = sqrt((x * x) + (y * y) + (z * z));
		qx = x / normU;
		qy = y / normU;
		qz = z / normU;

		//quaternion q setup
		qw = cos(theta / 2);
		qx = qx * sin(theta / 2);
		qy = qy * sin(theta / 2);
		qz = qz * sin(theta / 2);

		//set the rotation matrix

		this->m_mat[0][0] = (qw * qw) + (qx * qx) - (qy * qy) - (qz * qz);
		this->m_mat[0][1] = (2 * qx * qy) - (2 * qw * qz);
		this->m_mat[0][2] = (2 * qx * qz) + (2 * qw * qy);
		this->m_mat[0][3] = 0;

		this->m_mat[1][0] = (2 * qx * qy) + (2 * qw * qz);
		this->m_mat[1][1] = (qw * qw) - (qx * qx) + (qy * qy) - (qz * qz);
		this->m_mat[1][2] = (2 * qy * qz) - (2 * qw * qx);
		this->m_mat[1][3] = 0;

		this->m_mat[2][0] = (2 * qx * qz) - (2 * qw * qy);
		this->m_mat[2][1] = (2 * qy * qz) + (2 * qw * qx);
		this->m_mat[2][2] = (qw * qw) - (qx * qx) - (qy * qy) + (qz * qz);
		this->m_mat[2][3] = 0;
	}

	void setRotationX(float x) 
	{
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);
	}

	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.m_x + this->m_mat[1][3] * minor.m_y + this->m_mat[2][3] * minor.m_z +
			this->m_mat[3][3] * minor.m_w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.m_x / det;
			out.m_mat[1][i] = pow(-1.0f, i) * v.m_y / det;
			out.m_mat[2][i] = pow(-1.0f, i) * v.m_z / det;
			out.m_mat[3][i] = pow(-1.0f, i) * v.m_w / det;
		}

		this->setMatrix(out);
	}

	void operator *=(const Matrix4x4 &matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
					m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
			}
		}

		::memcpy(m_mat, out.m_mat, sizeof(float) * 16);
	}

	Matrix4x4 operator *(Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
					m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
			}
		}

		return out;
	}

	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}

	Vector3D getZDirection()
	{
		return Vector3D(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}

	Vector3D getYDirection()
	{
		return Vector3D(m_mat[1][0], m_mat[1][1], m_mat[1][2]);
	}

	Vector3D getXDirection()
	{
		return Vector3D(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}

	Vector3D getTranslation()
	{
		return Vector3D(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;

		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();

		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	~Matrix4x4()
	{

	}

public:
	float m_mat[4][4] = {};
};

_declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};