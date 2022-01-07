md_apply_hdr_save()
/*
 微商补货点击新增
*/
{
    char base_str[500],supply_unit_num_id[20];

	//获取固定代理商ID supply_unit_num_id
	strcpy(supply_unit_num_id,lr_eval_string(mendian_supply_unit_num_id()));
	lr_save_string(supply_unit_num_id,"supply_unit_num_id");
    //微商ID：md_sub_unit_num_id  补货单序列：md_sequence_num
    strcpy(base_str,lr_eval_string("{\"type_num_id\":1,\"remark\":\"\","
								   "\"supply_unit_num_id\":{supply_unit_num_id},"
								   "\"sub_unit_num_id\":{md_sub_unit_num_id},"
								   "\"apply_logistics_type\":0,\"apply_num_id\":\"{md_sequence_num}\","
								   "\"div_num_id\":0,\"order_date\":\"{order_date}\"}"));
	lr_save_string(base_str,"base_str");
	strcpy(base_str,base64_encode(lr_eval_string("{base_str}"),strlen(base_str)));
	lr_save_string(base_str,"base_str");
    web_reg_find("Text=\"code\":0","Savecount=apply_hdr_save_code_count",LAST);//设置检查点

	web_add_header("Authorization","{md_author}");
	web_set_sockets_option("SSL_VERSION","TLS");
    lr_start_transaction("apply_hdr_save");
    web_custom_request("apply_hdr_save",
		"URL={url}",
		"Method=POST",
		"Resource=0",
		"RecContentType=application/x-www-form-urlencoded",
		"Referer=",
		"Mode=HTTP",
		"EncType=application/x-www-form-urlencoded",
		"Body=timestamp={timestamp}&method=ykcloud.scm.replenish.apply.hdr.save&sid={md_sid}&sign=&params={base_str}",
		LAST);
	if(atoi(lr_eval_string("{apply_hdr_save_code_count}"))>0){
			lr_end_transaction("apply_hdr_save",LR_PASS);
		}else{
            lr_end_transaction("apply_hdr_save",LR_FAIL);
			 if (rerun_value()==0) {
				  return -1;
			 }
		} 
	return 0;
}
