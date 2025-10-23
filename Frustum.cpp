//---------------------------------------------------------------------
//---------------------------------------------------------------------
// The Nonlinear Game Engine (NGE) version 1.0
// (c) Mikael Fridenfalk
// All rights reserved
// Pending patent SE2330492-6
// The engine is a template for use in the course:
// Real-Time Graphics Programming for Games 1, 7.5 c, 2024
// Uppsala University, Sweden
// Other use requires a written permission from the copyright holder
//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include "Frustum.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// 3D Math
//---------------------------------------------------------------------
//---------------------------------------------------------------------
inline void Frustum::Vec_CrossProd(double * out, const double * a, const double * 
b){
 out[0] = a[1] * b[2] - b[1] * a[2];
 out[1] = b[0] * a[2] - a[0] * b[2];
 out[2] = a[0] * b[1] - b[0] * a[1];
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
inline double Frustum::Vec_DotProd(const double * a, const double * b){
 return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
inline void Frustum::Vec_Normalize(double * a){
 double invNorm = 1./sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
 if (fabs(invNorm) > 1.0e-20) For (i,3) a[i] *= invNorm;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// Evaluate Frustum Coords
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Frustum::Frustum_Screen2Space(double space[3],
 int x, int y, bool isFarClip){
 int viewport[4];
 double modelview[16], projection[16];
 double winX, winY, posX, posY, posZ;
 glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
 glGetDoublev(GL_PROJECTION_MATRIX, projection);
 glGetIntegerv(GL_VIEWPORT, viewport);
 winX = double(x);
 winY = double(viewport[3] - y);
 double winZ = double(isFarClip);
 gluUnProject(winX, winY, winZ,
 modelview, projection, viewport,
 &posX, &posY, &posZ);
 space[0] = posX; space[1] = posY; space[2] = posZ;
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Frustum::Frustum_EvalCoords(){
 //--------------------------------------------NearClip
 Frustum_Screen2Space(mUL0, 0, 0, false);//UpLeft
 Frustum_Screen2Space(mDL0, 0, sH, false);//DownLeft
 Frustum_Screen2Space(mUR0, sW, 0, false);//UpRight
 Frustum_Screen2Space(mDR0, sW, sH, false);//DownRight
 //--------------------------------------------FarClip
 Frustum_Screen2Space(mUL1, 0, 0, true);//UpLeft
 Frustum_Screen2Space(mDL1, 0, sH, true);//DownLeft
 Frustum_Screen2Space(mUR1, sW, 0, true);//UpRight
 Frustum_Screen2Space(mDR1, sW, sH, true);//DownRight
 //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// Evaluate Frustum Plane Normals
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Frustum::Frustum_EvalPlaneNormals(){
 //--------------------------------------------
 //--------------------------------------------
 For (i,3) FrustumEye[i] = mEye[i];
 //--------------------------------------------
 //--------------------------------------------
 double a[3], b[3];
 //--------------------------------------------
 //--------------------------------------------Right
 For (i,3) a[i] = mDR1[i] - FrustumEye[i];
 For (i,3) b[i] = mUR1[i] - FrustumEye[i];
 Vec_CrossProd(mN_Right,a,b);
 Vec_Normalize(mN_Right);
 //--------------------------------------------
 //--------------------------------------------
 // A2.2
 //--------------------------------------------
 //--------------------------------------------
// mPlanes[LEFT].normal = Vec_CrossProd(mCamUp, mCamRight);
// mPlanes[LEFT].d = -Vec_DotProd(mPlanes[LEFT].normal, mCamPos);
// mPlanes[TOP].normal = Vec_CrossProd(mCamRight, mCamForward);
// mPlanes[TOP].d = -Vec_DotProd(mPlanes[TOP].normal, mCamPos);
// mPlanes[BOTTOM].normal = Vec_CrossProd(mCamForward, mCamRight);
// mPlanes[BOTTOM].d = -Vec_DotProd(mPlanes[BOTTOM].normal, mCamPos);
// mPlanes[NEAR].normal = mCamForward;
// mPlanes[NEAR].d = -Vec_DotProd(mPlanes[NEAR].normal, mCamPos + mNearPlane * 
mCamForward);
// mPlanes[FAR].normal = -mCamForward;
// mPlanes[FAR].d = -Vec_DotProd(mPlanes[FAR].normal, mCamPos + mFarPlane * 
mCamForward);
//}
 //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//[ A2.2
 //--------------------------------------------
 //--------------------------------------------Up
 For(i, 3) a[i] = mUL1[i] - FrustumEye[i];
 For(i, 3) b[i] = mUR1[i] - FrustumEye[i];
 Vec_CrossProd(mN_Up, b, a);
 Vec_Normalize(mN_Up);
 //--------------------------------------------
 //--------------------------------------------Left
 For(i, 3) a[i] = mUL1[i] - FrustumEye[i];
 For(i, 3) b[i] = mDL1[i] - FrustumEye[i];
 Vec_CrossProd(mN_Left, a, b);
 Vec_Normalize(mN_Left);
 //--------------------------------------------
 //--------------------------------------------Down
 For(i, 3) a[i] = mDR1[i] - FrustumEye[i];
 For(i, 3) b[i] = mDL1[i] - FrustumEye[i];
 Vec_CrossProd(mN_Down, b, a);
 Vec_Normalize(mN_Down);
 //--------------------------------------------
 //--------------------------------------------Far
 For(i, 3) a[i] = mUR1[i] - mUL1[i];
 For(i, 3) b[i] = mUR1[i] - mDL1[i] ;
 Vec_CrossProd(mN_Far, a, b);
 Vec_Normalize(mN_Far);
 //--------------------------------------------
 //--------------------------------------------Near
 For(i, 3) a[i] = mUL0[i] - mDL0[i];
 For(i, 3) b[i] = mUR0[i] - mUL0[i];
 Vec_CrossProd(mN_Near, a, b);
 Vec_Normalize(mN_Near);
 //--------------------------------------------
 //--------------------------------------------
 //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//] A2.2
 //--------------------------------------------
 //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Frustum::Frustum_Draw(){
 //--------------------------------------------
 glColor4ub(70,160,255,127);
 //--------------------------------------------
 glEnable(GL_LIGHTING);
 //--------------------------------------------
 glEnable(GL_BLEND);
 //--------------------------------------------
 glBegin(GL_QUADS);
 //--------------------------------------------Down
 glNormal3dv(mN_Down);
 glVertex3dv(mDL0); glVertex3dv(mDL1);
 glVertex3dv(mDR1); glVertex3dv(mDR0);
 //--------------------------------------------Far
 glNormal3dv(mN_Far);
 glVertex3dv(mDR1); glVertex3dv(mUR1);
 glVertex3dv(mUL1); glVertex3dv(mDL1);
 //--------------------------------------------Right
 glNormal3dv(mN_Right);
 glVertex3dv(mDR0); glVertex3dv(mDR1);
 glVertex3dv(mUR1); glVertex3dv(mUR0);
 //--------------------------------------------Left
 glNormal3dv(mN_Left);
 glVertex3dv(mUL0); glVertex3dv(mUL1);
 glVertex3dv(mDL1); glVertex3dv(mDL0);
 //--------------------------------------------Up
 glNormal3dv(mN_Up);
 glVertex3dv(mUR0); glVertex3dv(mUR1);
 glVertex3dv(mUL1); glVertex3dv(mUL0);
 //--------------------------------------------Near
 glNormal3dv(mN_Near);
 glVertex3dv(mDR0); glVertex3dv(mUR0);
 glVertex3dv(mUL0); glVertex3dv(mDL0);
 //--------------------------------------------
 glEnd();
 //--------------------------------------------
 //glDisable(GL_LIGHTING);
 //--------------------------------------------
 //glDisable(GL_BLEND);
 //--------------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
// Determine if the Bounding Sphere is Inside the Frustum Volume
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int Frustum::Frustum_CullObj(const double pos[3], double r){
 //--------------------------------------------
 if (!mFrustumCullingON) return 0;
 //--------------------------------------------
 double v[3];
 //--------------------------------------------
 For (i,3) v[i] = mDL0[i] - pos[i];
 //--------------------------------------------Dark Red
 if (Vec_DotProd(v,mN_Near) > r) return 1;
 //--------------------------------------------
 For (i,3) v[i] = mDL1[i] - pos[i];
 //--------------------------------------------Red
 if (Vec_DotProd(v,mN_Far) > r) return 2;
 //--------------------------------------------
 For(i, 3) v[i] = pos[i] - FrustumEye[i];
 //--------------------------------------------Orange
 if (Vec_DotProd(v, mN_Left) > r) return 3;
 //--------------------------------------------Yellow
 if (Vec_DotProd(v, mN_Right) > r) return 4;
 //--------------------------------------------Green
 if (Vec_DotProd(v, mN_Up) > r) return 5;
 //--------------------------------------------Dark Blue
 if (Vec_DotProd(v, mN_Down) > r) return 6;
 //--------------------------------------------Blue
 return 0;
 //--------------------------------------------
 
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Frustum::Draw_Sphere(const double p[3], double r){
 glPushMatrix();
 glTranslated(p[0],p[1],p[2]);
 gluSphere(mQuadratic,(double)r,32,32);
 glPopMatrix();
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
void Frustum::Frustum_Test(){
 //----------------------------------------
 double p[][3] = {
 {0.6,1.6,-0.8},{1.,1.6,-0.8},{1.4,1.6,-0.8},//1
 {10.6,1.6,1},{11,1.6,1},{11.4,1.6,1},//2
 
 {3.6,1.6,-0.8},{4.,1.6,-0.8},{4.4,1.6,-0.8},//3
 {3.6,1.6,2.8},{4.,1.6,2.8},{4.4,1.6,2.8},//4
 
 {4,2,1},{4,2.4,1},{4,2.8,1},//5
 {4,0.4,1},{4,0.8,1},{4,1.2,1},//6
 };
 double r = .3;
 int N = sizeof(p)/sizeof(double)/3;
 //----------------------------------------
 glShadeModel(GL_SMOOTH);
 glEnable(GL_LIGHTING);
 For (i,N){
 int inside = Frustum_CullObj(p[i],r);
 switch (inside) {
 case 1: glColor3ub(127,0,0); break;//Dark Red
 case 2: glColor3ub(255,0,0); break;//Red
 case 3: glColor3ub(255,127,0); break;//Orange
 case 4: glColor3ub(255,255,0); break;//Yellow
 case 5: glColor3ub(0,255,0); break;//Green
 case 6: glColor3ub(0,0,63); break;//Dark Blue
 case 0: glColor3ub(0,0,255); break;//Blue
 }
 Draw_Sphere(p[i],r);
 }
 //glDisable(GL_LIGHTING);
 //glShadeModel(GL_FLAT);
 //----------------------------------------
}
//---------------------------------------------------------------------
//---------------------------------------------------------------------
