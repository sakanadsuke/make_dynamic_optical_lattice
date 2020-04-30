#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
int height = 1600;
int width = 2560;
double rate = 0.02;

//double rate = 0.02;
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "header.h"
#include "unistd.h"

vector<vector<string> > table;   // 読み込んだCSVファイルの内容
vector<vector<string> > table_2;   // 読み込んだCSVファイルの内容
int table_count = 0;
int timer_count = 0;
string last_time_stamp;
/*
void Idle(){

    struct stat st;
    string time_stamp;
    int file_status_check;

    cout << "sleep\n";
    //一定時間経過後、index.csvが更新されているかチェックする。
    
    while(1){
      stat("./index.csv", &st);
      time_stamp = asctime(localtime(&st.st_mtime));

      file_status_check = check_file_status(time_stamp);
      if(file_status_check == 1){
	glutPostRedisplay();
      }
      cout << "sleep\n";
      sleep(5);
    }
    
}
*/

void timer(int value){

    struct stat st;
    string time_stamp;
    int file_status_check;

    cout << "sleep\n";
    //一定時間経過後、indgex.csvが更新されているかチェックする。
   
    stat("./index.csv", &st);
    time_stamp = asctime(localtime(&st.st_mtime)); //新しいタイムスタンプの取得
    
    if(timer_count > 0){
      int file_status_check = time_stamp.compare(last_time_stamp);      
      if(file_status_check != 0){//タイムスタンプが一致していない場合＝ファイルが更新された
	cout << "file updated \n";
	last_time_stamp = time_stamp;
	glutPostRedisplay();
      }
    }else{
      last_time_stamp = time_stamp;
    }
    timer_count++;
    glutTimerFunc(2000 , timer , 0);
    
}


void make_square(int x, int y){
  
  double x_r, y_r;
  double x_length, y_length;
  x_r = x * (2.0 / width) - 1;
  y_r = y * (2.0 / height) - 1;
  x_length = rate * height / width;
  //x_length = 0.02 * height / width;
  y_length = rate;
  glColor3d(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  glVertex2d(x_r, y_r);
  glVertex2d(x_r + x_length, y_r);
  glVertex2d(x_r + x_length, y_r + y_length);
  glVertex2d(x_r, y_r + y_length);
  glEnd();
  
}

void delete_square(int x, int y){
  
  cout << "delete\n";
  double x_r, y_r;
  double x_length, y_length;
  x_r = x * (2.0 / width) - 1;
  y_r = y * (2.0 / height) - 1;
  x_length = rate * height / width;
  //x_length = 0.02 * height / width;
  y_length = rate;
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  glVertex2d(x_r, y_r);
  glVertex2d(x_r + x_length, y_r);
  glVertex2d(x_r + x_length, y_r + y_length);
  glVertex2d(x_r, y_r + y_length);
  glEnd();
  
}

/*
void idle(void)
{
   glutPostRedisplay();
  Idle();
}

*/

int check(int i, int j, int table_count){

  if(table_count % 2 != 0){//table_countが奇数のとき、更新されたtableを確認
    for (int row = 0; row < table.size(); row++){
      vector<string> record;  // １行分の内容
      record = table[row];    // １行分読み込む
      // １セルずつ読み込んでコンソールに出力する
      
      
      //cout << stoi(record[1]);
      if(stoi(record[0]) == i && stoi(record[1]) == j){
	//cout  <<  i  << j << "\n" ;
	cout << table.size() << "size_1\n";
	return 1;
      }
    }
  }else{//table_countが奇数のとき、最初のチェックで更新されたtable_2を確認

    for (int row = 0; row < table_2.size(); row++){
      vector<string> record_2;  // １行分の内容
      record_2 = table_2[row];    // １行分読み込む
      // １セルずつ読み込んでコンソールに出力する
      
      
      //cout << stoi(record[1]);
      if(stoi(record_2[0]) == i && stoi(record_2[1]) == j){
	//cout  <<  i  << j << "\n" ;
	cout << table_2.size() << "size_2\n";
	return 1;
      }
    }
  }
  return 0;
}

int display_count = 0;

void display(void)
{

  int x_distance;
  int y_distance;
  int x, y;
  int i = 0;
  int j = 0;

  if(display_count % 2 == 0){
    table_count ++;
    if(table_count % 2 == 1){
      cout << "table_count o\n" ;
      GetContents("index.csv", table);
    }else{
      cout << "table_count e\n" ;
      GetContents("index.csv", table_2);
    }
    cout << "aa\n";
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    
    glBegin(GL_QUADS);
    x_distance = 50;
    y_distance = 50;
    
    for (y = 0; y < height * (1 - rate) ; y = y + y_distance) {
      for (x = 0; x < width * (1 - rate) ; x = x + x_distance) {
	//cout << i << " " << j << " " <<  "check !\n";
	if(check(i, j, table_count)){    
	  //cout << "make squere\n";
	  make_square(x, y);      
	}else if(check(i, j, table_count-1)){
	  cout << "hoooo\n";
	  delete_square(x,y);
	}
	i++;      
      }
      i = 0;
      j++;
    }
        
    cout << table_count << "\n";
    glEnd();
    glFlush();
  }
  display_count++;

}



void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0,0, w, h);

  /* 透視変換行列の設定 */

  /* モデルビュー変換行列の設定 */
  glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
}



void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':  /* '\033' は ESC の ASCII コード */
    exit(0);
    //case 'r':
    //glutPostRedisplay();
    //break;
  default:
    //glutIdleFunc(0);
    break;
  }
   
}



int main(int argc, char *argv[])
{
   // 変数を定義する
  bool status = false;    // メソッドのステータス
  string filename = "index.csv"; // ファイル名
 
  // CSVファイルの内容を取得する
  status = GetContents(filename, table);
  GetContents(filename, table_2);
  if (!status)
    {
      // 取得に失敗した場合はエラー終了する
      return -1;
    }
 
  // 確認のためにコンソールに内容を出力する
  for (int row = 0; row < table.size(); row++)
    {
      vector<string> record;  // １行分の内容
      record = table[row];    // １行分読み込む
      // １セルずつ読み込んでコンソールに出力する
      for (int column = 0; column < record.size(); column++)
	{
	  cout << record[column];
	  // 末尾の列でない場合はカンマを出力する
	  if (column < record.size() - 1)
	    {
	      cout << ",";
	    }
	}
      cout << endl;
    }
 
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  //glutFullScreen();
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyboard);
  //glutIdleFunc(Idle);
  glutTimerFunc(2000 , timer , 0);
  init();
  glutMainLoop();
  return 0;
}
