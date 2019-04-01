abstract class Account{
	public abstract void lend(double price);
	public abstract void payback(double price);
}

class CheckingAccount extends Account{
private double money;
private double rate = 0.1; 

@Override
public void lend(double price){
// TODO Auto-generated method stub
try {
	this.money = price * (1+rate) ;
	System.out.println("您一共借了"+price+"元"+",您需要还"+this.money+"元");
}
catch(Exception e){
	System.out.println("请输入借款金额！");
}
}

@Override
public void payback(double price) {
// TODO Auto-generated method stub
try {
	if(this.money - price < 0){
		System.out.println("您只需要还"+this.money+"元");
	}
	else {
		this.money = this.money - price;
		System.out.println("您还需要还"+this.money+"元");
	}
}
catch(Exception e){
	System.out.println("请输入还款金额！");
}
}
}



class SavingsAccount extends Account{
private double money;
private double rate = 0.2; 

@Override
public void lend(double price){
// TODO Auto-generated method stub
try {
	this.money = price * (1+rate) ;
	System.out.println("您一共借了"+price+"元"+",您需要还"+this.money+"元");
}
catch(Exception e){
	System.out.println("请输入借款金额！");
}
}

@Override
public void payback(double price) {
// TODO Auto-generated method stub
try {
	if(this.money - price < 0){
		System.out.println("您只需要还"+this.money+"元");
		this.money = this.money - price;
		System.out.println("您还需要还"+this.money+"元");
	}
	else {
		this.money = this.money - price;
		System.out.println("您还需要还"+this.money+"元");		
	}
}
catch(Exception e){
	System.out.println("请输入还款金额！");
}
}
}


class BusinessAccount extends Account{
private double money;
private double rate = 0.3; 

@Override
public void lend(double price){
// TODO Auto-generated method stub
try {
	this.money = price * (1+rate) ;
	System.out.println("您一共借了"+price+"元"+",您需要还"+this.money+"元");
}
catch(Exception e){
	System.out.println("请输入借款金额！");
}
}

@Override
public void payback(double price) {
// TODO Auto-generated method stub
try {
	if(this.money - price < 0 ){
		System.out.println("您只需要还"+this.money+"元");
	}
	else {
		this.money = this.money - price;
		System.out.println("您还需要还"+this.money+"元");
	}
}
catch(Exception e){
	System.out.println("请输入还款金额！");
}
}
}
public class train {

public static void main(String[] args) {
	CheckingAccount a = new CheckingAccount();
	SavingsAccount b = new SavingsAccount();
	BusinessAccount c = new BusinessAccount();
	a.lend(100);
	b.lend(100);
	c.lend(100);
	a.payback(110);
	b.payback(120);
	c.payback(130);
}
}