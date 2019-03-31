package com.example.internetapp;

import android.support.v7.app.ActionBarActivity;
import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.Toast;


public class MainActivity extends ActionBarActivity{

	private WebView show = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //启用标题自带进度条
        requestWindowFeature(Window.FEATURE_PROGRESS);
        
        setContentView(R.layout.activity_main);
        
        //获取对应组件
        this.show = (WebView)findViewById(R.id.show);
        //加载百度网页
        this.show.loadUrl("http://baidu.com");
        this.show.setWebViewClient(new WebViewClient(){
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                // TODO Auto-generated method stub
                   //返回值是true的时候控制去WebView打开，为false调用系统浏览器或第三方浏览器
                 view.loadUrl(url);
                return true;
            }
           });
        //开启javascript
        WebSettings settings = this.show.getSettings();
        settings.setJavaScriptEnabled(true);
        //设置视频可以全屏
       /* settings.setUseWideViewPort(true); // 关键点
        settings.setAllowFileAccess(true); // 允许访问文件
        settings.setSupportZoom(true); // 支持缩放
        settings.setLoadWithOverviewMode(true);*/
 
        //优先使用缓存
        this.show.getSettings().setCacheMode(WebSettings.LOAD_CACHE_ELSE_NETWORK);
        //判断页面加载过程
       this.show.setWebChromeClient(new WebChromeClient() {
            @Override
            public void onProgressChanged(WebView view, int newProgress) {
                // TODO Auto-generated method stub
                //Log.i("s", String.valueOf(newProgress));
            	if (newProgress == 100) {
                    // 网页加载完成 隐藏进度条
                	setProgressBarVisibility(false);
                } else {// 加载中
                	setProgressBarVisibility(true);
                	setProgress(newProgress * 100);
                }

            }
        });
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
    public boolean onKeyDown(int keyCode,KeyEvent event)
    {
    	//回退且还有网页缓存，则倒退
    	if (keyCode == KeyEvent.KEYCODE_BACK
    			&& this.show.canGoBack())
    	{
			this.show.goBack();
			return true;
    	}
    	return super.onKeyDown(keyCode, event);
    }
}
