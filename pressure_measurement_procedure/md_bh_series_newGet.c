md_bh_series_newGet()
/*
  获取补货单单号
*/
{
	char base_str[100],base_str_gys[100];

    strcpy(base_str,lr_eval_string("{\"series_name\":\"scm_bl_apply_hdr_apply_num_id\"}"));
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");
    web_reg_find("Text=\"code\":0","Savecount=mdbh_newGet_code_count",LAST);//设置检查点
	//微商获取补货单号序列
    web_reg_save_param("md_sequence_num","RB=\"}","LB=\"sequence_num\":\"",LAST);//用关联函数取值 

	web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("client_series_newGet");
    web_custom_request("md_bh_series_newGet",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=gb.core.sequence.client.series.newGet&sid={md_sid}&sign=&params={base_str}",
		LAST);
	if(atoi(lr_eval_string("{mdbh_newGet_code_count}"))>0){
			lr_end_transaction("client_series_newGet",LR_PASS);
		}else{
            lr_end_transaction("client_series_newGet",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

    //查询代理商
	strcpy(base_str_gys,lr_eval_string("{\"sql_id\":\"YKPPAY-0099\","
									   "\"on_line\":true,\"input_param\":{\"unit_num_ids\":\"\"},"
									   "\"page_num\":1,\"page_size\":500}"));
	lr_save_string(base_str_gys,"base_str_gys");
	strcpy(base_str_gys,base64_encode(lr_eval_string("{base_str_gys}"),strlen(base_str_gys)));
	lr_save_string(base_str_gys,"base_str_gys");
    web_reg_find("Text=\"code\":0","Savecount=gys_query_code_count",LAST);//设置检查点

	web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("gys_query-YKPPAY-0099");
    web_custom_request("gys_query",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={md_sid}&sign=&params={base_str_gys}",
		LAST);
	if(atoi(lr_eval_string("{gys_query_code_count}"))>0){
			lr_end_transaction("gys_query-YKPPAY-0099",LR_PASS);
		}else{
            lr_end_transaction("gys_query-YKPPAY-0099",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 
	return 0;
}
