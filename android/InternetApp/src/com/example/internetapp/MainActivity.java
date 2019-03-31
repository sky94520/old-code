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
        //���ñ����Դ�������
        requestWindowFeature(Window.FEATURE_PROGRESS);
        
        setContentView(R.layout.activity_main);
        
        //��ȡ��Ӧ���
        this.show = (WebView)findViewById(R.id.show);
        //���ذٶ���ҳ
        this.show.loadUrl("http://baidu.com");
        this.show.setWebViewClient(new WebViewClient(){
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                // TODO Auto-generated method stub
                   //����ֵ��true��ʱ�����ȥWebView�򿪣�Ϊfalse����ϵͳ�����������������
                 view.loadUrl(url);
                return true;
            }
           });
        //����javascript
        WebSettings settings = this.show.getSettings();
        settings.setJavaScriptEnabled(true);
        //������Ƶ����ȫ��
       /* settings.setUseWideViewPort(true); // �ؼ���
        settings.setAllowFileAccess(true); // ��������ļ�
        settings.setSupportZoom(true); // ֧������
        settings.setLoadWithOverviewMode(true);*/
 
        //����ʹ�û���
        this.show.getSettings().setCacheMode(WebSettings.LOAD_CACHE_ELSE_NETWORK);
        //�ж�ҳ����ع���
       this.show.setWebChromeClient(new WebChromeClient() {
            @Override
            public void onProgressChanged(WebView view, int newProgress) {
                // TODO Auto-generated method stub
                //Log.i("s", String.valueOf(newProgress));
            	if (newProgress == 100) {
                    // ��ҳ������� ���ؽ�����
                	setProgressBarVisibility(false);
                } else {// ������
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
    	//�����һ�����ҳ���棬����
    	if (keyCode == KeyEvent.KEYCODE_BACK
    			&& this.show.canGoBack())
    	{
			this.show.goBack();
			return true;
    	}
    	return super.onKeyDown(keyCode, event);
    }
}
