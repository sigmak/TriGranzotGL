/*
	Author: sigmak (dwfree74@gmail.com)  
	Date: 30-11-15 00:13
	Description: OpenGL Triangle Draw and function test
*/

/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <gl/gl.h>
#include <tchar.h>
#include <stdio.h>

/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

HWND hWndGL;
HDC hDCGL;
HGLRC hRCGL;

HINSTANCE g_hInst;
HWND hEdit, hEdit2;
HWND hBtn, hBtn2;

float floatVar;
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
      0, 0, 800, 800,
      NULL, NULL, hInstance, NULL);

  /* create gl window */
    hWndGL = CreateWindow("button","Triangle GL",WS_CHILD | WS_VISIBLE ,
            20,20,600,600,hWnd,(HMENU)0,g_hInst,NULL);

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
    DisableOpenGL (hWndGL, hDCGL, hRCGL);

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
         int x,y,w,h;
         x=640;
         y=10;
         w=40;
         h=10;
         
         hEdit=CreateWindow("edit","hEdit",WS_CHILD | WS_VISIBLE ,
                            x,y,w,h,hWnd,(HMENU)100,g_hInst,NULL);
         SetWindowText(hEdit,"0.125");
       
         x+=w+10;
         w=60;
         h=20;
         hBtn = CreateWindow("button","hBtn",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                x,y,w,h,hWnd,(HMENU)0,g_hInst,NULL);       
                

         x=640;
         y=60;
         w=40;
         h=10;
         
         hEdit2=CreateWindow("edit","hEdit2",WS_CHILD | WS_VISIBLE ,
                            x,y,w,h,hWnd,(HMENU)101,g_hInst,NULL);
         SetWindowText(hEdit2,"0.67");
       
         x+=w+10;
         w=60;
         h=20;
         hBtn2 = CreateWindow("button","hBtn2",WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                x,y,w,h,hWnd,(HMENU)1,g_hInst,NULL);       	
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
             TCHAR buffer[256];
             GetWindowText(hEdit, buffer, 255);
               //MessageBox(hWnd,buffer,"Button",MB_OK);
              
             //http://stackoverflow.com/questions/2826097/how-to-print-a-float-number-to-visual-c-messagebox             
             floatVar = atof((const char *)buffer); 
/*            
             char sBuffer[256];
             WCHAR wBuffer[256];
             swprintf(wBuffer, L"%f", floatVar);           
             wtoc(sBuffer,wBuffer);      
             MessageBox(hWnd,sBuffer,"Button",MB_OK);
*/
            /* OpenGL animation code goes here */
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);

            glPushMatrix ();
            //glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (0.87f, -0.5f);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-0.87f, -0.5f);
            glEnd ();
            glPopMatrix ();

            SwapBuffers (hDCGL);

            //theta += 1.0f;
            Sleep (1);

            break;
           
        case 1:
             TCHAR buffer2[256];
             GetWindowText(hEdit2, buffer2, 255);
               //MessageBox(hWnd,buffer2,"Button",MB_OK);
             floatVar = atof((const char *)buffer2); 

            // »ï°¢Çü Âü°í : http://soen.kr/lecture/library/opengl/opengl-2.htm
            /* OpenGL animation code goes here */
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);

            glPushMatrix ();
            //glRotatef (theta, 0.0f, 0.0f, 1.0f);
            glBegin (GL_TRIANGLES);
            glColor3f (1.0f, 0.0f, 0.0f);   glVertex2f (0.0f, 1.0f);
            glColor3f (0.0f, 1.0f, 0.0f);   glVertex2f (floatVar, -0.5f);
            glColor3f (0.0f, 0.0f, 1.0f);   glVertex2f (-floatVar, -0.5f);
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
