import java.io.Serializable;
import java.util.ArrayList;


	public class Question implements Serializable
	{
		private String question = null;
		private ArrayList<String> answerList = null;
		private int curIndex = 0;
	
	public Question(String question, ArrayList<String> answerList, int curIndex) {
		super();
		this.question = question;
		this.answerList = answerList;
		this.curIndex = curIndex;
	}
	public String getQuestion() {
		return question;
	}
	public void setQuestion(String question) {
		this.question = question;
	}
	public ArrayList<String> getAnswerList() {
		return answerList;
	}
	public void setAnswerList(ArrayList<String> answerList) {
		this.answerList = answerList;
	}
	public int getCurIndex() {
		return curIndex;
	}
	public void setCurIndex(int curIndex) {
		this.curIndex = curIndex;
	}
	@Override
	public String toString() {
		return "问题 " + question + "\n" + answerList+
				"\n正确答案=" + getAnswerStr();
	}
	public char getAnswerStr()
	{
		char ch = (char) ('A' + curIndex);
		
		return ch;
	}
}
