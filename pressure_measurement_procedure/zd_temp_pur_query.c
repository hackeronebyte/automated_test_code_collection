zd_temp_pur_query()
/**
 * 集单查询
 */
{

    char base_str[1024],base_str2[1024],url[50],zd_series_num[10],all_pre_po_num_id[10];
    strcpy(url,lr_eval_string(base_url()));
    lr_save_string(url,"url");

	//查询未确认全部
    strcpy(base_str,lr_eval_string("{\"sql_id\":\"YKPPAY-SCM-PRE-PO-LIST\","
								   "\"on_line\":true,\"input_param\":{\"status_num_id\":\"1\","
								   "\"begin_date\":\"{today}\",\"end_date\":\"{today}\"},"
								   "\"page_num\":1,\"page_size\":1000}"));
    lr_convert_string_encoding(base_str, LR_ENC_SYSTEM_LOCALE, LR_ENC_UTF8,"base_str" );
    strcpy(base_str,lr_eval_string("{base_str}"));
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");


	web_reg_find("Text=\"code\":0","Savecount=temp_pur_query_code_count",LAST);//设置检查点
	//关联获取预采单号:
    web_reg_save_param("all_pre_po_num_id","RB=\",","LB=\"pre_po_num_id\":\"","ORD=ALL",LAST);//用关联函数取值

	web_add_header("Authorization","{zd_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
	lr_start_transaction("YKPPAY-SCM-PRE-PO-LIST");
	web_custom_request("temp_pur_query",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=hg.poykl.data.export&sid={zd_sid}&sign=&params={base_str}",
		LAST);
	if(atoi(lr_eval_string("{temp_pur_query_code_count}"))>0){
			lr_end_transaction("YKPPAY-SCM-PRE-PO-LIST",LR_PASS);
		}else{
			lr_end_transaction("YKPPAY-SCM-PRE-PO-LIST",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 

	sprintf(all_pre_po_num_id,"{all_pre_po_num_id_%d}",rand()%(atoi(lr_eval_string("{all_pre_po_num_id_count}")))+1);
	lr_save_string (lr_eval_string(all_pre_po_num_id),"all_pre_po_num_id" );
    

	return 0;
}
