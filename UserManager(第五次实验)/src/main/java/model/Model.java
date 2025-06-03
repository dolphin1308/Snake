package model;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

import dbutil.Dbconn;
import entity.User;

public class Model {
	private Statement stat;
	private PreparedStatement ps;
	private ResultSet rs;
	Dbconn s=new Dbconn();
	public int update(Integer id,String name,String password){
		int a=0;
		try {
			Connection conn=s.getConnection();
			String sql="update user set name=?,password=? where id=?";
			ps=conn.prepareStatement(sql);
			ps.setInt(3, id);
			ps.setString(1, name);
			ps.setString(2, password);
			a=ps.executeUpdate();
			s.closeAll(conn,ps,rs);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return a;
	}
	public int insert(Integer id,String name,String password){
		int a=0;
		try {
			Connection conn=s.getConnection();
			String sql="insert user values(?,?,?)";
			ps=conn.prepareStatement(sql);
			ps.setInt(1, id);
			ps.setString(2, name);
			ps.setString(3, password);
			a=ps.executeUpdate();
			s.closeAll(conn,ps,rs);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return a;
	}
	//根据id删除
	public int delete(Integer id){
		int a=0;
		try { 
			Connection conn=s.getConnection();
			String sql="delete from user where id=?";
			ps=conn.prepareStatement(sql);
			ps.setInt(1, id);
			a=ps.executeUpdate();
			s.closeAll(conn,ps,rs);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return a;
	}
	//根据id查找
	public User load(Integer id){
		User user=new User();
		try { 
			Connection conn=s.getConnection();
			String sql="select * from user where id=?";
			ps=conn.prepareStatement(sql);
			ps.setInt(1, id);
			rs=ps.executeQuery();
			while(rs.next()){
				user=new User();
				user.setId(rs.getInt("id"));
				user.setName(rs.getString("name"));
				user.setPassword(rs.getString("password"));
			} 
			s.closeAll(conn,stat,rs);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return user;
	}
	public ArrayList userSelect(){
		ArrayList<User> users=new ArrayList<User>();
		try { 
			Connection conn=s.getConnection();
			String sql="select * from user";
			ps=conn.prepareStatement(sql);
			rs=ps.executeQuery();
			User user;
			while(rs.next()){
				user=new User();
				user.setId(rs.getInt("id"));
				user.setName(rs.getString("name"));
				user.setPassword(rs.getString("password"));
				users.add(user);
			} 
			s.closeAll(conn,stat,rs);
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return users;
	}
}