package org.cbparty.jnilib;

import java.io.File;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.ServiceConnection;
import android.net.Uri;
import android.os.Environment;
import android.os.IBinder;
import android.util.Log;
import cn.waps.AppConnect;

public class CBNativeInterface {
	public static final String DEBUG_TAG = "cocos2d-x debug info";
	public static final String PARAM_SPLIT = "###"; 
	public static Cocos2dxActivity activity;
	public static String NativeInvoke(String method, String param) {
		try {
			final String[] params = param.split(PARAM_SPLIT);
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
								AppConnect.getInstance(CBNativeInterface.activity).close();
							}
						}).setNegativeButton("取消", new DialogInterface.OnClickListener() {
							
							@Override
							public void onClick(DialogInterface dialog, int which) {
								// TODO Auto-generated method stub
								
							}
						}).show();
					}
					
				});
			} else if (method.equals("Share")) {
				String file_name = params[0];
				String tip = params[1];
				Log.d(DEBUG_TAG," picture name is " + file_name + " tip is " + tip);
				Intent shareIntent = new Intent(Intent.ACTION_SEND);
				File file = new File(file_name);
				
				shareIntent.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(file));
				if (!tip.equals("")) {
					shareIntent.putExtra(Intent.EXTRA_TEXT, tip);
				}
				shareIntent.setType("image/jpg");
				CBNativeInterface.activity.startActivity(Intent.createChooser(shareIntent, "分享"));
			}
			else if (method.equals("MakeFilePath")) {
				String cocos2dFilePath = params[0];
				Log.d(DEBUG_TAG," cocos2dFIle path is " + cocos2dFilePath);
				String sdDir = null;
				boolean sdCardExist = Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED);
				if(sdCardExist) {
					Log.d(DEBUG_TAG," have sd card,sdcard path is " + Environment.getExternalStorageDirectory().toString());
					sdDir = Environment.getExternalStorageDirectory().toString() + "/CBShareRes/";
				} else {
					Log.d(DEBUG_TAG,"no sd card");
					sdDir = cocos2dFilePath + "CBShareRes/";
				}
				File file = new File(sdDir);
				if (!file.exists()) {
					Log.d(DEBUG_TAG," 文件目录不存在。生成文件目录：" + sdDir);
					if(file.mkdirs()) {
						Log.d(DEBUG_TAG," 文件目录生成成功");
					} else {
						Log.d(DEBUG_TAG," 文件目录生成失败");
					}
				} else {
					Log.d(DEBUG_TAG," 文件目录已存在");
				}
				return sdDir;
			} else if (method.equals("showAdWall")) {
				CBNativeInterface.activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						// TODO Auto-generated method stub
						AppConnect.getInstance(CBNativeInterface.activity).showGameOffers(CBNativeInterface.activity);
					}
					
				});
			} else if (method.equals("showPopAd")) {
				CBNativeInterface.activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						// TODO Auto-generated method stub
						if (AppConnect.getInstance(CBNativeInterface.activity).hasPopAd(CBNativeInterface.activity)) {
							AppConnect.getInstance(CBNativeInterface.activity).showPopAd(CBNativeInterface.activity);
						}
					}
					
				});
			} else if (method.equals("enterBackGround")) {
				CBNativeInterface.activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						// TODO Auto-generated method stub
						String innerMethod = params[0];
						Log.d(CBNativeInterface.DEBUG_TAG," inner method is " + innerMethod);
						if (innerMethod.equals("earnInBG")) {
							Log.d(CBNativeInterface.DEBUG_TAG," 后台倒计时开始");
							Intent intent = new Intent(CBNativeInterface.activity,CountTimeService.class);
							CBNativeInterface.activity.bindService(intent, serviceConn, Context.BIND_AUTO_CREATE);
						} else {
							Log.d(CBNativeInterface.DEBUG_TAG," 切入后台，不倒计时");
						}
					}
					
				});
			} else if (method.equals("enterForeGround")) {
				CBNativeInterface.activity.runOnUiThread(new Runnable() {

					@Override
					public void run() {
						// TODO Auto-generated method stub
						if (CTService != null) {
							Log.d(CBNativeInterface.DEBUG_TAG," 进入前台，停止后台倒计时");
							CBNativeInterface.CallCInMainThread("updateEarn", CTService.getTimeAdd() + "");
							CBNativeInterface.activity.unbindService(serviceConn);
						} else {
							Log.d(CBNativeInterface.DEBUG_TAG," 进入前台，service为null");
						}
					} 
					
				});
 			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return "";
	}
	
	private static CountTimeService  CTService = null; 
	
	private static ServiceConnection serviceConn = new ServiceConnection() {

		@Override
		public void onServiceConnected(ComponentName name, IBinder bind) {
			// TODO Auto-generated method stub
			Log.d(DEBUG_TAG,"service connected");
			CTService = ((CountTimeService.MyBinder)bind).getService();
		}

		@Override
		public void onServiceDisconnected(ComponentName arg0) {
			// TODO Auto-generated method stub
			Log.d(DEBUG_TAG,"service DisConnected");
			CTService = null;
		}
		
	};
	
	public static void onCreate() {
		CBNativeInterface.activity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				AppConnect.getInstance(CBNativeInterface.activity);
				AppConnect.getInstance(CBNativeInterface.activity).initPopAd(CBNativeInterface.activity);
			}
			
		});
	}
	
	public static native String CallC(String method, String param);
	public static void CallCInMainThread(String method, String param) {
		final String methodFinal = method;
		final String paramFinal = param;
		CBNativeInterface.activity.runOnGLThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				Log.d(DEBUG_TAG, "run in main thread");
				CallC(methodFinal,paramFinal);
			}
			
		});
	}
}
