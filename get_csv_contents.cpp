#include "header.h"
//
//  CSVを取得する
//      filename    読み込むファイル名
//      table       読み込んだCSVの内容
//      delimiter   区切り文字(今回はデフォルトでカンマ)
//


bool GetContents(const string& filename, vector<vector<string> >& table, const char delimiter)
{
  // ファイルを開く
  table.clear();
  fstream filestream(filename);
  if (!filestream.is_open())
    {
      // ファイルが開けなかった場合は終了する
      return false;
    }
 
  // ファイルを読み込む
  while (!filestream.eof())
    {
      // １行読み込む
      string buffer;
      filestream >> buffer;
 
      // ファイルから読み込んだ１行の文字列を区切り文字で分けてリストに追加する
      vector<string> record;              // １行分の文字列のリスト
      istringstream streambuffer(buffer); // 文字列ストリーム
      string token;                       // １セル分の文字列
      while (getline(streambuffer, token, delimiter))
	{
	  // １セル分の文字列をリストに追加する
	  record.push_back(token);
	}
 
      // １行分の文字列を出力引数のリストに追加する
      table.push_back(record);
    }
 
  return true;
}
