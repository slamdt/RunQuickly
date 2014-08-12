/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.CBParty.RunQuickly;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.Toast;

public class RunQuicky extends Cocos2dxActivity{

	RunQuicky context;
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		context = this;
	}
	
    static {
         System.loadLibrary("game");
    }
    
    @Override
    public boolean onKeyDown(int keyCode,KeyEvent event) {
    	Log.d("cocos2d-x", " on keydown");
    	if (keyCode == KeyEvent.KEYCODE_BACK) {
    		Log.d("cocos2d-x", " back press");
    		new AlertDialog.Builder(this).setTitle("确定退出游戏？").setPositiveButton("确定", new DialogInterface.OnClickListener() {
				
				@Override
				public void onClick(DialogInterface arg0, int arg1) {
					// TODO Auto-generated method stub
					Toast.makeText(context, "你退出了游戏", Toast.LENGTH_SHORT).show();
					System.exit(0);
				}
			}).setNegativeButton("取消", new DialogInterface.OnClickListener() {
				
				@Override
				public void onClick(DialogInterface arg0, int arg1) {
					// TODO Auto-generated method stub
					Toast.makeText(context, "你取消了退出游戏", Toast.LENGTH_SHORT).show();			
				}
			}).show();
    		return true;
    	} else {
    		return super.onKeyDown(keyCode, event);
    	}
    }
}
