package org.cbparty.jnilib;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

public class CountTimeService extends Service{

	private MyBinder myBinder = new MyBinder();
	private int timeAdd = 0;
	Timer timer;
	@Override
	public IBinder onBind(Intent arg0) {
		// onBind返回myBinder后才能响应ServiceConnection的onServiceConnected方法，如果返回NUll则不会响应onServiceConnected。
		Log.d(CBNativeInterface.DEBUG_TAG," service onBind");
		timer.schedule(new TimerTask() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				timeAdd ++;
				Log.d(CBNativeInterface.DEBUG_TAG," timeAdd is " + timeAdd);
			}
			
		}, 1000, 1000);
		return myBinder;
	}
	
	@Override
	public void onRebind(Intent intent) {
		Log.d(CBNativeInterface.DEBUG_TAG," service onReBind");
		super.onRebind(intent);
	}
	
	@Override
	public boolean onUnbind(Intent intent) {
		Log.d(CBNativeInterface.DEBUG_TAG," service onUnBind");
		timer.cancel();
		timeAdd = 0;
		return super.onUnbind(intent);
		
	}
	
	@Override
	public void onCreate() {
		Log.d(CBNativeInterface.DEBUG_TAG," service create");
		timer = new Timer(true);
		super.onCreate();
	}
	
	@Override
	public void onDestroy() {
		Log.d(CBNativeInterface.DEBUG_TAG," service destroy");
		super.onDestroy();
	}
	
	@Override
	public void onStart(Intent intent, int startId) {
		Log.d(CBNativeInterface.DEBUG_TAG," service start");
		super.onStart(intent, startId);
	}
	
	public int getTimeAdd () {
		return timeAdd;
	}

	public class MyBinder extends Binder {
		CountTimeService getService() {
			return CountTimeService.this;
		}
	}
}
