package org.cbparty.jnilib;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.util.Log;

public class CBNativeInterface {
	public static final String DEBUG_TAG = "cocos2d-x debug info";
	public static Cocos2dxActivity activity;
	public static String NativeInvoke(String method, String param) {
		try {
			Log.d(DEBUG_TAG," jni call here,method is " + method + " ,param is " + param);
			if (method.equals("quitGame")) {
				CBNativeInterface.activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						// TODO Auto-generated method stub
						new AlertDialog.Builder(CBNativeInterface.activity).setTitle("确定退出游戏?").setPositiveButton("确定", new DialogInterface.OnClickListener() {
							
							@Override
							public void onClick(DialogInterface arg0, int arg1) {
								// TODO Auto-generated method stub
								CBNativeInterface.CallC("QuitGameSure", "");	
							}
						}).setNegativeButton("取消", new DialogInterface.OnClickListener() {
							
							@Override
							public void onClick(DialogInterface dialog, int which) {
								// TODO Auto-generated method stub
								
							}
						}).show();
					}
					
				});
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return "";
	}
	
	public static native String CallC(String method, String param);
}
