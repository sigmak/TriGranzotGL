/*
	Author: sigmak (dwfree74@gmail.com)  
	Date: 30-11-15 00:13
	Description: OpenGL Triangle Draw and function test

	Date: 30-11-15 02:38
	Description: Triangle Control move, scale and Granzot draw 

	Date: 30-11-15 03:01
	Description: Granzot style modify add
*/


/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void setTriangleGLpos(float x0, float y0,
                    float x1, float y1,
                    float x2, float y2);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
void star5(float x_shift, float y_shift, float star_radius);
void star6(float x_shift, float y_shift, float star_radius);

HWND hWndGL;
HDC hDCGL;
HGLRC hRCGL;

HINSTANCE g_hInst;

static HWND hwnd_st_x[3], hwnd_ed_x[3];
static HWND hwnd_st_y[3], hwnd_ed_y[3];

static HWND hwnd_st_dx, hwnd_ed_dx;
static HWND hwnd_st_dy, hwnd_ed_dy;

static HWND hwnd_st_sx, hwnd_ed_sx;
static HWND hwnd_st_sy, hwnd_ed_sy;

static HWND hwnd_bt_default, hwnd_bt_dxy, hwnd_bt_sxy;
static HWND hwnd_bt_granjoe5, hwnd_bt_granjoe6;

float fx[3],fy[3], fsx, fsy;
int winGLwidth;
TCHAR buffer[256];
char sBuffer[256];
WCHAR wBuffer[256];
int icntScale;
/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    //wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.hbrBackground = (HBRUSH) GetStockObject (GRAY_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "TriGranzotGL";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "TriGranzotGL", "OpenGL Triangle & Granzot", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 950, 700,
      NULL, NULL, hInstance, NULL);

  /* create gl window */
    hWndGL = CreateWindow("static","Triangle GL",WS_CHILD | WS_VISIBLE ,
            10,10,600,600,hWnd,(HMENU)0,g_hInst,NULL);
    icntScale=0;
    
    /* enable OpenGL for the window */
    EnableOpenGL (hWndGL, &hDCGL, &hRCGL);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */
/*
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);

            glPushMatrix ();
            glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (0.87f, -0.5f);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-0.87f, -0.5f);
            glEnd ();
            glPopMatrix ();

            SwapBuffers (hDC);

            theta += 1.0f;
            Sleep (1);
  */
        }
    }

    /* shutdown OpenGL */
    //DisableOpenGL (hWndGL, hDCGL, hRCGL);

    /* destroy the window explicitly */
    DestroyWindow (hWndGL);
    DestroyWindow (hWnd);

    return msg.wParam;
}

// http://forums.codeguru.com/showthread.php?336106-WCHAR*-to-CHAR*
void wtoc(CHAR* Dest, const WCHAR* Source)
{
    int i = 0;

    while(Source[i] != '\0')
    {
        Dest[i] = (CHAR)Source[i];
        ++i;
    }
}


 float radius;
 float radius2;

 float small_radius;
 float DEGINRAD;
 int Nums;
 float x_left;
 float y_left;

 float x_left2;
 float y_left2;

/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
           int x, w, y, h;

           fx[0]=0.0;fy[0]=1.0;
           fx[1]=0.87;fy[1]=-0.5;
           fx[2]=-0.87;fy[2]=-0.5;

           winGLwidth=10+600; //OPENGL 넓이

           //x0 ---------------------------------------------------------------------------------
           y = 10; h = 20;
           x = winGLwidth+10; w = 30;
           hwnd_st_x[0] = CreateWindow("static", "ST_X0", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(501), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_x[0], "X0: ");
       
           x += w+10; w = 50;
           hwnd_ed_x[0] = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(502), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
            
           swprintf(wBuffer, L"%f", fx[0]);           
           wtoc(sBuffer,wBuffer);      
           SetWindowText(hwnd_ed_x[0], sBuffer);            
           //y0 ---------------------------------------------------------------------------------
           x += w+10; w = 30;
           hwnd_st_y[0] = CreateWindow("static", "ST_Y0", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(503), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_y[0], ", Y0: ");
       
           x += w+10; w = 50;
           hwnd_ed_y[0] = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(504), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);

           swprintf(wBuffer, L"%f", fy[0]);           
           wtoc(sBuffer,wBuffer);      
           SetWindowText(hwnd_ed_y[0], sBuffer);            

           //x1 ---------------------------------------------------------------------------------
           y += h+10; h=20;
           x = winGLwidth+10; w = 30;
           hwnd_st_x[1] = CreateWindow("static", "ST_X0", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(505), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_x[1], "X1: ");
       
           x += w+10; w = 50;
           hwnd_ed_x[1] = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(506), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           swprintf(wBuffer, L"%f", fx[1]);           
           wtoc(sBuffer,wBuffer);      
           SetWindowText(hwnd_ed_x[1], sBuffer);            

           //y1 ---------------------------------------------------------------------------------
           x += w+10; w = 30;
           hwnd_st_y[1] = CreateWindow("static", "ST_Y1", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(507), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_y[1], ", Y1: ");
       
           x += w+10; w = 50;
           hwnd_ed_y[1] = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(508), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           swprintf(wBuffer, L"%f", fy[1]);           
           wtoc(sBuffer,wBuffer);      
           SetWindowText(hwnd_ed_y[1], sBuffer);            

           //x2 ---------------------------------------------------------------------------------
           y += h+10; h=20;
           x = winGLwidth+10; w = 30;
           hwnd_st_x[2] = CreateWindow("static", "ST_X2", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(509), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_x[2], "X2: ");
       
           x += w+10; w = 50;
           hwnd_ed_x[2] = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(510), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           swprintf(wBuffer, L"%f", fx[2]);           
           wtoc(sBuffer,wBuffer);      
           SetWindowText(hwnd_ed_x[2], sBuffer);            

           //y2 ---------------------------------------------------------------------------------
           x += w+10; w = 30;
           hwnd_st_y[2] = CreateWindow("static", "ST_Y2", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(511), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_y[2], ", Y2: ");
       
           x += w+10; w = 50;
           hwnd_ed_y[2] = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(512), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           swprintf(wBuffer, L"%f", fy[2]);           
           wtoc(sBuffer,wBuffer);      
           SetWindowText(hwnd_ed_y[2], sBuffer);            
           //-------------------------------------------------------------------------------
           x += w+10; w = 120;
           hwnd_bt_default = CreateWindow("button","default_view",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                     x,y,w,h ,hWnd,(HMENU)0,g_hInst,NULL);

           //dX ---------------------------------------------------------------------------------
           y += h+10+50; h=20;
           x = winGLwidth+10; w = 30;
           hwnd_st_dx = CreateWindow("static", "ST_dX", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(513), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_dx, "dX: ");
       
           x += w+10; w = 40;
           hwnd_ed_dx = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(514), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_ed_dx, "0.3");            
           //dY ---------------------------------------------------------------------------------
           x += w+10; w = 30;
           hwnd_st_dy = CreateWindow("static", "ST_dY", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(515), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_dy, ", dY: ");
       
           x += w+10; w = 40;
           hwnd_ed_dy = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(516), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_ed_dy, "0.3");            
           
           x += w+10; w = 80;
           hwnd_bt_dxy = CreateWindow("button","dxy_view",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                     x,y,w,h ,hWnd,(HMENU)1,g_hInst,NULL);

           //sX ---------------------------------------------------------------------------------
           y += h+10; h=20;
           x = winGLwidth+10; w = 30;
           hwnd_st_sx = CreateWindow("static", "ST_sX", WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(517), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_sx, "sX: ");
       
           x += w+10; w = 40;
           hwnd_ed_sx = CreateWindow("edit", "", WS_CHILD | WS_VISIBLE | WS_TABSTOP | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(518), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_ed_sx, "1.5");            
           //sY ---------------------------------------------------------------------------------
           x += w+10; w = 30;
           hwnd_st_sy = CreateWindow("static", "ST_sY",
                                      WS_CHILD | WS_VISIBLE | WS_TABSTOP,
                                      x, y, w, h,
                                      hWnd, (HMENU)(519), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_st_sy, ", dY: ");
       
           x += w+10; w = 40;
           hwnd_ed_sy = CreateWindow("edit", "",
                                      WS_CHILD | WS_VISIBLE | WS_TABSTOP
                                      | ES_LEFT | WS_BORDER,
                                      x, y, w, h,
                                      hWnd, (HMENU)(520), (HINSTANCE) GetWindowLong (hWnd, GWL_HINSTANCE), NULL);
           SetWindowText(hwnd_ed_sy, "1.5");            

           x += w+10; w = 80;
           hwnd_bt_sxy = CreateWindow("button","sxy_view",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                     x,y,w,h ,hWnd,(HMENU)2,g_hInst,NULL);
           //------------------------------------------------------------------------
           y += h+10; h=20;
           x = winGLwidth+10; w = 120;
           hwnd_bt_granjoe5 = CreateWindow("button","GranJoe star5",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                     x,y,w,h ,hWnd,(HMENU)3,g_hInst,NULL);

           y += h+10; h=20;
           x = winGLwidth+10; w = 120;
           hwnd_bt_granjoe6 = CreateWindow("button","GranJoe star6",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                     x,y,w,h ,hWnd,(HMENU)4,g_hInst,NULL);


        return 0;
        
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;
     case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case 0:
             for(int i=0;i<=2; i++){
                 GetWindowText(hwnd_ed_x[i], buffer, 255);
                 fx[i]=atof((const char *)buffer); 

                 GetWindowText(hwnd_ed_y[i], buffer, 255);
                 fy[i]=atof((const char *)buffer); 
             }
             if(icntScale==0){
               glScaled (0.5 *1.0f ,0.5 *1.0f ,0.0f);
               icntScale=icntScale+1;
             }
             setTriangleGLpos(fx[0],fy[0], fx[1],fy[1], fx[2],fy[2]);
            
            break;
           
        case 1:
             for(int i=0;i<=2; i++){
                 GetWindowText(hwnd_ed_x[i], buffer, 255);
                 fx[i]=atof((const char *)buffer); 

                 GetWindowText(hwnd_ed_dx, buffer, 255);
                 fx[i]+=atof((const char *)buffer); 

                 GetWindowText(hwnd_ed_y[i], buffer, 255);
                 fy[i]=atof((const char *)buffer); 

                 GetWindowText(hwnd_ed_dy, buffer, 255);
                 fy[i]+=atof((const char *)buffer); 

             }
             setTriangleGLpos(fx[0],fy[0], fx[1],fy[1], fx[2],fy[2]);
            break;

        case 2:
             for(int i=0;i<=2; i++){
                 GetWindowText(hwnd_ed_x[i], buffer, 255);
                 fx[i]=atof((const char *)buffer); 

                 GetWindowText(hwnd_ed_y[i], buffer, 255);
                 fy[i]=atof((const char *)buffer); 

             }
             GetWindowText(hwnd_ed_sx, buffer, 255);
             fsx=atof((const char *)buffer); 
             GetWindowText(hwnd_ed_sy, buffer, 255);
             fsy=atof((const char *)buffer); 

             glScaled (fsx *1.0f ,fsy *1.0f ,0.0f); // 정말 Scale 되는데...ㅜ.;

             setTriangleGLpos(fx[0],fy[0], fx[1],fy[1], fx[2],fy[2]);
            
            break;
        case 3: //그란죠 그리기
             if(icntScale>0){
               glScaled (1.0f /0.5f,1.0f/0.5f ,0.0f);
               icntScale=0;
             }
            
             //우선 원부터 그리기
             radius=0.7;
             radius2=0.6;
            
             small_radius=0.21;
             DEGINRAD=3.14159/180;
             Nums=360;
             x_left = 0.0;
             y_left = 0.1;
            
             x_left2 = 0.01;
             y_left2 = 0.11;

            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix ();
           
            // 큰 원
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_LINE_STRIP);
            for (int i=0; i<=360;i++)  {
               float degInRad=i*DEGINRAD;
               glVertex2f(cos(degInRad)*radius + x_left, sin(degInRad)*radius + y_left);
            }           
            glEnd ();

            // 작은 원
            glBegin(GL_LINE_STRIP);
            for (int i=0; i<=360;i++)  {
               float degInRad=i*DEGINRAD;
               glVertex2f(cos(degInRad)*radius2 + x_left2, sin(degInRad)*radius2 + y_left2);
            }           
            glEnd ();
           
            //별모양 그리는 함수
            star5(0.01,0.1,0.6); //0.063

/*           
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (x0, y0);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (x1, y1);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (x2, y2);
*/
            glEnd ();
            glPopMatrix ();

            SwapBuffers (hDCGL);

            //theta += 1.0f;
            Sleep (1);


               
            break;

        case 4: //그란죠 그리기
             if(icntScale>0){
               glScaled (1.0f /0.5f,1.0f/0.5f ,0.0f);
               icntScale=0;
             }
            
             if(icntScale>0){
               glScaled (1.0f /0.5f,1.0f/0.5f ,0.0f);
               icntScale=0;
             }
            
             //우선 원부터 그리기
             radius=0.7;
             radius2=0.6;
            
             small_radius=0.21;
             DEGINRAD=3.14159/180;
             Nums=360;
             x_left = 0.0;
             y_left = 0.1;
            
             x_left2 = 0.01;
             y_left2 = 0.11;

            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix ();
           
            // 큰 원
            glColor3f(1.0,1.0,1.0);
            glBegin(GL_LINE_STRIP);
            for (int i=0; i<=360;i++)  {
               float degInRad=i*DEGINRAD;
               glVertex2f(cos(degInRad)*radius + x_left, sin(degInRad)*radius + y_left);
            }           
            glEnd ();

            // 작은 원
            glBegin(GL_LINE_STRIP);
            for (int i=0; i<=360;i++)  {
               float degInRad=i*DEGINRAD;
               glVertex2f(cos(degInRad)*radius2 + x_left2, sin(degInRad)*radius2 + y_left2);
            }           
            glEnd ();
           
            //별모양 그리는 함수
            star6(0.01,0.1,0.6); //0.063

/*           
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (x0, y0);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (x1, y1);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (x2, y2);
*/
            glEnd ();
            glPopMatrix ();

            SwapBuffers (hDCGL);

            //theta += 1.0f;
            Sleep (1);


               
            break;
           
        }
        return 0;



    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}

/*******************
 * 좌표 이용하는 방식
 *******************/
void setTriangleGLpos(float x0, float y0,
                    float x1, float y1,
                    float x2, float y2){
           // 삼각형 참고 : http://soen.kr/lecture/library/opengl/opengl-2.htm
            /* OpenGL animation code goes here */
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);
            

            glPushMatrix ();
            //glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (x0, y0);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (x1, y1);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (x2, y2);
            glEnd ();
            glPopMatrix ();

            SwapBuffers (hDCGL);

            //theta += 1.0f;
            Sleep (1);
}

// 출처 : http://blog.naver.com/PostView.nhn?blogId=shimchan2&logNo=70009963396
//삼각형 3개를 조합해서 별 만들기
void star5(float x_shift, float y_shift, float star_radius){
// float star_radius=0.063;
 float DEGINRAD=3.14159/180;
 glColor3f(1.0,1.0,1.0);
 glBegin(GL_LINE_STRIP);
   // 별모양 그리기 각도 이미지 참고 : http://sexy.pe.kr/tc/archive/201304
  glVertex2f(cos(18 *DEGINRAD)*star_radius  + x_shift, sin(18 *DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((18 + 72+72)*DEGINRAD)*star_radius  + x_shift, sin((18 + 72+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((18 + 72+72 + 72+72)*DEGINRAD)*star_radius  + x_shift, sin((18 + 72+72+ 72+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((18+72)*DEGINRAD)*star_radius  + x_shift, sin((18+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((18+72 + 72+72)*DEGINRAD)*star_radius  + x_shift, sin((18+72 + 72+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((18)*DEGINRAD)*star_radius  + x_shift, sin((18)*DEGINRAD)*star_radius  + y_shift);
 glEnd();
}

// 출처 : http://blog.naver.com/PostView.nhn?blogId=shimchan2&logNo=70009963396 
//삼각형 3개를 조합해서 별 만들기
void star6(float x_shift, float y_shift, float star_radius){
// float star_radius=0.063;
 float DEGINRAD=3.14159/180 * 5/6;
 int gap;
 glColor3f(1.0,1.0,1.0);
 glBegin(GL_LINE_STRIP);
  gap=-180; //18
   // 별모양 그리기 각도 이미지 참고 : http://sexy.pe.kr/tc/archive/201304 
  glVertex2f(cos(gap *DEGINRAD)*star_radius  + x_shift, sin(gap *DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((gap + 72+72)*DEGINRAD)*star_radius  + x_shift, sin((gap + 72+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((gap + 72+72 + 72+72)*DEGINRAD)*star_radius  + x_shift, sin((gap + 72+72+ 72+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((gap)*DEGINRAD)*star_radius  + x_shift, sin((gap)*DEGINRAD)*star_radius  + y_shift);
 glEnd();

 glBegin(GL_LINE_STRIP);
 
   gap=180;
   // 별모양 그리기 각도 이미지 참고 : http://sexy.pe.kr/tc/archive/201304 
  glVertex2f(cos(gap *DEGINRAD)*star_radius  + x_shift, sin(gap *DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((gap + 72+72)*DEGINRAD)*star_radius  + x_shift, sin((gap + 72+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((gap + 72+72 + 72+72)*DEGINRAD)*star_radius  + x_shift, sin((gap + 72+72+ 72+72)*DEGINRAD)*star_radius  + y_shift);
  glVertex2f(cos((gap)*DEGINRAD)*star_radius  + x_shift, sin((gap)*DEGINRAD)*star_radius  + y_shift);
  
 glEnd();
 
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
