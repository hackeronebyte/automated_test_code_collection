zd_login()
{
	char base_str[1024],url[50],u_name[20],pwd[30],tenant_numid[20];
	strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");
    
	strcpy(u_name,lr_eval_string(zongdian_loginName()));
	lr_save_string(u_name,"u_name");
	strcpy(pwd,lr_eval_string(zongdian_loginPassword()));
	lr_save_string(pwd,"pwd");

	strcpy(tenant_numid,lr_eval_string(zongdian_tenant_num_id()));
	lr_save_string(tenant_numid,"zd_tenant_numid");
    
    if (rerun_value()==0) {
	    //调式环境随机取值 tenant_num_id
		strcpy(base_str,lr_eval_string("{\"work_nums\":\"{u_name}\",\"password\":\"{pwd}\",\"channel_num_id\":2,\"tenant_num_id\":{zd_merchantid_value}}"));
		lr_convert_string_encoding(base_str, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str" );
        strcpy(base_str,lr_eval_string("{base_str}"));
	}else{
		//运行环境固定取值 tenant_num_id （生产环境）
		strcpy(base_str,lr_eval_string("{\"work_nums\":\"{u_name}\",\"password\":\"{pwd}\",\"channel_num_id\":2,\"tenant_num_id\":{zd_tenant_numid}}"));

		lr_convert_string_encoding(base_str, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str" );
        strcpy(base_str,lr_eval_string("{base_str}"));
      }

	
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");
	/**
	 * {"code":0,"message":"成功","full_message":null,"work_nums":"管理员",
	 * "sid":"57340ce6c46942c5bb1a343cc65b21df", "salt":"bfcd4118dcf0889b83d6e41eaf5dcc20",
	 * "empe_name":"管理员","sub_unit_num_id":100049,"sub_unit_name":"生鲜超市总部","physical_storages":null}
	 */
	web_reg_find("Text=\"code\":0","Savecount=login_code_count",LAST);//设置检查点
    web_reg_save_param("zd_sid","RB=\",","LB=\"sid\":\"",LAST);//用关联函数取值
	web_reg_save_param("zd_sub_unit_num_id","RB=,","LB=\"sub_unit_num_id\":",LAST);//用关联函数取值
	web_reg_save_param("zd_author","RB=\r\n","LB=Authorization: ",LAST);//用关联函数取值
	//https
	web_set_sockets_option("SSL_VERSION","TLS");

	lr_start_transaction("login");
	web_custom_request("login",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=app_key=12000&timestamp={timestamp}&method=ykcloud.user.by.worknums.password.login&sign=&params={base_str}",
		LAST);
	 if(atoi(lr_eval_string("{login_code_count}"))>0){
			lr_end_transaction("login",LR_PASS);
		}else{
            lr_end_transaction("login",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		}  
	return 0;
}
