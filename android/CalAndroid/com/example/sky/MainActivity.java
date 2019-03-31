package com.example.sky;

import java.util.ArrayList;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends ActionBarActivity{
	private Calculate calculate = null;
	private StringBuilder strBuilder = null;
	private TextView textView = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //����������ʽ
        calculate = new Calculate();
        strBuilder = new StringBuilder();
        
        textView = (TextView) findViewById(R.id.output);
        //���¼�������
        EventListener eventListener = new EventListener(this);
        SignalListener signalListener = new SignalListener(this);
        
        findViewById(R.id.clear).setOnClickListener(eventListener);
        findViewById(R.id.decrease).setOnClickListener(eventListener);
        findViewById(R.id.equal).setOnClickListener(eventListener);
        //���ַ�������
        int[] idArray = {R.id.one,R.id.two,R.id.three,R.id.four
        		,R.id.five,R.id.six,R.id.seven,R.id.eight,R.id.nine
        		,R.id.left,R.id.right,R.id.add,R.id.sub
        		,R.id.multiple,R.id.mod,R.id.divide};
        for(int id:idArray){
        	findViewById(id).setOnClickListener(signalListener);
        }
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
    public void addChar(char ch)
    {
    	this.strBuilder.append(ch);
    	//����text view
    	this.textView.setText(strBuilder.toString());
    }
    public void removeLastChar()
    {
    	//ɾ�������ַ�
    	int length = strBuilder.length();
    	
    	if (length > 0)
    	{
    	this.strBuilder.deleteCharAt(length - 1);
    	//����text view
    	this.textView.setText(strBuilder.toString());
    	}
    	else
    		Toast.makeText(this, "�Ѿ�Ϊ��", 1000);
    }
    public void removeAllChar()
    {
    	int length = strBuilder.length();
    	
    	if (length == 0)
    		return;
    	
    	this.strBuilder.delete(0, length);
    	//����text view
    	this.textView.setText(strBuilder.toString());
    }
    public void calculate()
    {
       	//��ȡ�ַ���
    	String text = this.strBuilder.toString();
    	if (text.isEmpty())
    		return ;
    	
    	ArrayList<String> list = this.calculate.getStringList(text);
    	ArrayList<String> post = this.calculate.getPostOrder(list);
    	
    	int result = this.calculate.calculate(post);
    	//��ʾ���
    	this.textView.setText(String.valueOf(result));
    	//����ַ���������
    	this.strBuilder.delete(0, strBuilder.length());
    	this.strBuilder.append(result);
    }
}
//�¼������� �� = c dec �ȵ�
class EventListener implements View.OnClickListener
{
	private MainActivity owner = null;
	
	public EventListener(MainActivity owner)
	{
		this.owner = owner;
	}
	@Override
	public void onClick(View arg0) {
		Button btn = (Button)arg0;
		String cmd = btn.getText().toString();
		
		switch(cmd){
		case "C": this.owner.removeAllChar(); break;
		case "decrease": this.owner.removeLastChar();break;
		case "=": this.owner.calculate(); break;
		}
	}
}
//���ż�����
class SignalListener implements View.OnClickListener
{
	private MainActivity owner = null;
	
	public SignalListener(MainActivity owner)
	{
		this.owner = owner;
	}
	@Override
	public void onClick(View arg0) {
		Button btn = (Button)arg0;
		// TODO Auto-generated method stub
		owner.addChar(btn.getText().charAt(0));
	}
}