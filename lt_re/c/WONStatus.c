/* lithtech.exe decompilation - module WONStatus */
#include "ghidra_types.h"

/* 004b3b80 size=2581 */

/* repo: libs/WONAPI/WONStatus.cpp */

char * __cdecl WONStatus_4b3b80(int param_1)

{
  if (param_1 < 0x2727) {
    if (param_1 == 0x2726) {
      return s_WS_WSAEINVAL_004dfa9c;
    }
    if (param_1 < -0x9c7) {
      if (param_1 == -0x9c8) {
        return s_WS_RoutingServG2_ClientAlreadyIn_004e02b0;
      }
      if (param_1 < -0x9ee) {
        if (param_1 == -0x9ef) {
          return s_WS_RoutingServG2_ShutdownTimerAl_004e07ec;
        }
        if (param_1 < -0xa32) {
          if (param_1 == -0xa33) {
            return s_WS_ProfileServ_InvalidWONUserNam_004e0aa8;
          }
          if (param_1 < -0xaf1) {
            if (param_1 == -0xaf2) {
              return s_WS_DBProxyServ_NoModule_004e0bdc;
            }
            switch(param_1) {
            case -2999:
              return s_WS_DBProxyServ_GameSpecificError_004e0bf4;
            case -0xb57:
              return s_WS_DBProxyServ_GameSpecificWarri_004e0c18;
            case -0xb54:
              return s_WS_DBProxyServ_GameSpecificError_004e0c4c;
            case -0xaf8:
              return s_WS_DBProxyServ_KeyNotUsed_004e0c74;
            case -0xaf7:
              return s_WS_DBProxyServ_InvalidCDKey_004e0c90;
            case -0xaf6:
              return s_WS_DBProxyServ_UserDoesNotExist_004e0cac;
            case -0xaf5:
              return s_WS_DBProxyServ_KeyInUse_004e0ccc;
            case -0xaf4:
              return s_WS_DBProxyServ_InvalidUserName_004e0ce4;
            case -0xaf3:
              return s_WS_DBProxyServ_UserExists_004e0d04;
            }
          }
          else {
            switch(param_1) {
            case -0xaf1:
              return s_WS_DBProxyServ_NoData_004e0acc;
            case -0xaf0:
              return s_WS_DBProxyServ_DBError_004e0ae4;
            case -0xa39:
              return s_WS_ProfileServ_RemoveNewsLetters_004e0afc;
            case -0xa38:
              return s_WS_ProfileServ_NoNewslettersProv_004e0b24;
            case -0xa37:
              return s_WS_ProfileServ_TooManyNewsletter_004e0b4c;
            case -0xa36:
              return s_WS_ProfileServ_UnfoundNewsletter_004e0b70;
            case -0xa35:
              return s_WS_ProfileServ_OtherError_004e0b98;
            case -0xa34:
              return s_WS_ProfileServ_AccountCreationDi_004e0bb4;
            }
          }
        }
        else {
          switch(param_1) {
          case -0xa32:
            return s_WS_ProfileServ_DatabaseError_004e0818;
          case -0xa31:
            return s_WS_ProfileServ_WONUserAlreadyExi_004e0838;
          case -0xa30:
            return s_WS_ProfileServ_BadWONUserPasswor_004e085c;
          case -0xa2f:
            return s_WS_ProfileServ_PartySourceEntryE_004e0880;
          case -0xa2e:
            return s_WS_ProfileServ_NewsletterEntryEx_004e08a8;
          case -0xa2d:
            return s_WS_ProfileServ_EmailAlreadyUsed_004e08d0;
          case -0xa2c:
            return s_WS_ProfileServ_PartySeqAlreadySe_004e08f0;
          case -0xa2b:
            return s_WS_ProfileServ_CountryNotFound_004e0914;
          case -0xa2a:
            return s_WS_ProfileServ_AgeRangeNotFound_004e0934;
          case -0xa29:
            return s_WS_ProfileServ_UserNotFound_004e0954;
          case -0xa28:
            return s_WS_ProfileServ_ProfileDoesNotExi_004e0970;
          case -0x9f6:
            return s_WS_RoutingServG2_TooManyRecipien_004e0994;
          case -0x9f5:
            return s_WS_RoutingServG2_TooManyMembersh_004e09b8;
          case -0x9f4:
            return s_WS_RoutingServG2_Throttled_004e09dc;
          case -0x9f3:
            return s_WS_RoutingServG2_SubscriptionDoe_004e09f8;
          case -0x9f2:
            return s_WS_RoutingServG2_SubscriptionDoe_004e0a24;
          case -0x9f1:
            return s_WS_RoutingServG2_SubscriptionAlr_004e0a50;
          case -0x9f0:
            return s_WS_RoutingServG2_ShutdownTimerDo_004e0a7c;
          }
        }
      }
      else {
        switch(param_1) {
        case -0x9ee:
          return s_WS_RoutingServG2_ServerFull_004e02d8;
        case -0x9ed:
          return s_WS_RoutingServG2_Pending_004e02f4;
        case -0x9ec:
          return s_WS_RoutingServG2_OffsetTooLarge_004e0310;
        case -0x9eb:
          return s_WS_RoutingServG2_ObserversNotAll_004e0330;
        case -0x9ea:
          return s_WS_RoutingServG2_ObjectDoesNotEx_004e0358;
        case -0x9e9:
          return s_WS_RoutingServG2_NoUsernameInCer_004e037c;
        case -0x9e8:
          return s_WS_RoutingServG2_NoPendingJoin_004e03a8;
        case -0x9e7:
          return s_WS_RoutingServG2_MustBeVisible_004e03c8;
        case -0x9e6:
          return s_WS_RoutingServG2_MustBeSelf_004e03e8;
        case -0x9e4:
          return s_WS_RoutingServG2_MustBeModerator_004e0404;
        case -0x9e3:
          return s_WS_RoutingServG2_MustBeClient_004e0428;
        case -0x9e2:
          return s_WS_RoutingServG2_MustBeCaptainOr_004e0448;
        case -0x9e1:
          return s_WS_RoutingServG2_MustBeCaptain_004e0474;
        case -0x9e0:
          return s_WS_RoutingServG2_MustBeAuthentic_004e0494;
        case -0x9df:
          return s_WS_RoutingServG2_MustBeAdmin_004e04bc;
        case -0x9de:
          return s_WS_RoutingServG2_LoginTypeNotSup_004e04dc;
        case -0x9dd:
          return s_WS_RoutingServG2_InvalidWONUserI_004e0504;
        case -0x9dc:
          return s_WS_RoutingServG2_InvalidPassword_004e0528;
        case -0x9db:
          return s_WS_RoutingServG2_InvalidContentT_004e054c;
        case -0x9da:
          return s_WS_RoutingServG2_GuestNamesReser_004e0570;
        case -0x9d9:
          return s_WS_RoutingServG2_GroupFull_004e0594;
        case -0x9d8:
          return s_WS_RoutingServG2_GroupDoesNotExi_004e05b0;
        case -0x9d7:
          return s_WS_RoutingServG2_GroupDeleted_004e05d4;
        case -0x9d6:
          return s_WS_RoutingServG2_GroupClosed_004e05f4;
        case -0x9d5:
          return s_WS_RoutingServG2_GroupAlreadyExi_004e0614;
        case -0x9d4:
          return s_WS_RoutingServG2_GroupAlreadyCla_004e0638;
        case -0x9d3:
          return s_WS_RoutingServG2_DuplicateDataOb_004e0660;
        case -0x9d2:
          return s_WS_RoutingServG2_ConnectFailure_004e0688;
        case -0x9d1:
          return s_WS_RoutingServG2_ClientNotPermit_004e06a8;
        case -0x9d0:
          return s_WS_RoutingServG2_ClientNotMuted_004e06cc;
        case -0x9cf:
          return s_WS_RoutingServG2_ClientNotInvite_004e06ec;
        case -0x9ce:
          return s_WS_RoutingServG2_ClientNotInGrou_004e0710;
        case -0x9cd:
          return s_WS_RoutingServG2_ClientNotBanned_004e0734;
        case -0x9cc:
          return s_WS_RoutingServG2_ClientDoesNotEx_004e0758;
        case -0x9cb:
          return s_WS_RoutingServG2_ClientBanned_004e077c;
        case -0x9ca:
          return s_WS_RoutingServG2_ClientAlreadyRe_004e079c;
        case -0x9c9:
          return s_WS_RoutingServG2_ClientAlreadyMu_004e07c8;
        }
      }
    }
    else if (param_1 < -0x4b9) {
      if (param_1 == -0x4ba) {
        return s_WS_DirServ_InvalidGetFlags_004dfe60;
      }
      if (param_1 < -0x5de) {
        if (param_1 == -0x5df) {
          return s_WS_AuthServ_CDKeyInUse_004e007c;
        }
        if (param_1 < -0x5e7) {
          if (param_1 == -0x5e8) {
            return s_WS_AuthServ_UserSeqInUse_004e0168;
          }
          if (param_1 < -0x76d) {
            if (param_1 == -0x76e) {
              return s_WS_EventServ_InvalidDataType_004e01f4;
            }
            switch(param_1) {
            case -0x9c7:
              return s_WS_RoutingServG2_ClientAlreadyEx_004e0214;
            case -0x9c6:
              return s_WS_RoutingServG2_ClientAlreadyBa_004e023c;
            case -0x9c5:
              return s_WS_RoutingServG2_CaptainRejected_004e0264;
            case -0x9c4:
              return s_WS_RoutingServG2_BlankNamesNotAl_004e0288;
            }
          }
          else if (param_1 < -0x76a) {
            if (param_1 == -0x76b) {
              return s_WS_EventServ_FailureStart_004e019c;
            }
            if (param_1 == -0x76d) {
              return s_WS_EventServ_InvalidDateTime_004e01b8;
            }
            if (param_1 == -0x76c) {
              return s_WS_EventServ_BufferingError_004e01d8;
            }
          }
          else if (param_1 == -0x5e9) {
            return s_WS_AuthServ_SetCUDError_004e0184;
          }
        }
        else {
          switch(param_1) {
          case -0x5e7:
            return s_WS_AuthServ_NotInCommunity_004e0094;
          case -0x5e6:
            return s_WS_AuthServ_InvalidCDKey_004e00b0;
          case -0x5e5:
            return s_WS_AuthServ_BadCommunity_004e00cc;
          case -0x5e4:
            return s_WS_AuthServ_InvalidUserName_004e00e8;
          case -0x5e3:
            return s_WS_AuthServ_BadPassword_004e0104;
          case -0x5e2:
            return s_WS_AuthServ_UserNotFound_004e011c;
          case -0x5e1:
            return s_WS_AuthServ_UserExists_004e0138;
          case -0x5e0:
            return s_WS_AuthServ_CRCFailed_004e0150;
          }
        }
      }
      else if (param_1 < -0x4c2) {
        if (param_1 == -0x4c3) {
          return s_WS_DirServ_PermissionExists_004dff5c;
        }
        if (param_1 < -0x4c7) {
          if (param_1 == -0x4c8) {
            return s_WS_DirServ_MultiGetFailedAllRequ_004dffec;
          }
          switch(param_1) {
          case -0x5de:
            return s_WS_AuthServ_CDKeyBanned_004e0014;
          case -0x5dd:
            return s_WS_AuthServ_BadCDKey_004e002c;
          case -0x5dc:
            return s_WS_AuthServ_BadPubKeyBlock_004e0044;
          case -0x5db:
            return s_WS_AuthServ_FailureStart_004e0060;
          }
        }
        else {
          switch(param_1) {
          case -0x4c7:
            return s_WS_DirServ_MultiGetPartialFailur_004dff78;
          case -0x4c6:
            return s_WS_DirServ_NoACLs_004dff9c;
          case -0x4c5:
            return s_WS_DirServ_MaxPermissions_004dffb0;
          case -0x4c4:
            return s_WS_DirServ_PermissionNotFound_004dffcc;
          }
        }
      }
      else {
        switch(param_1) {
        case -0x4c2:
          return s_WS_DirServ_InvalidACLType_004dfe7c;
        case -0x4c1:
          return s_WS_DirServ_DataObjectNotFound_004dfe98;
        case -0x4c0:
          return s_WS_DirServ_DataObjectExists_004dfeb8;
        case -0x4bf:
          return s_WS_DirServ_NoDataObjects_004dfed4;
        case -0x4be:
          return s_WS_DirServ_InvalidDataObject_004dfef0;
        case -0x4bd:
          return s_WS_DirServ_InvalidLifespan_004dff10;
        case -0x4bc:
          return s_WS_DirServ_InvalidMode_004dff2c;
        case -0x4bb:
          return s_WS_DirServ_InvalidKey_004dff44;
        }
      }
    }
    else if (param_1 < -0x13) {
      if (param_1 == -0x14) {
        return s_WS_CommServ_StatusCommon_BannedA_004dfd18;
      }
      switch(param_1) {
      case -0x4b9:
        return s_WS_DirServ_InvalidPath_004dfd40;
      case -0x4b8:
        return s_WS_DirServ_BadDataOffset_004dfd58;
      case -0x4b7:
        return s_WS_DirServ_MaxDataObjects_004dfd74;
      case -0x4b6:
        return s_WS_DirServ_EntityTooLarge_004dfd90;
      case -0x4b5:
        return s_WS_DirServ_AlreadyConnected_004dfdac;
      case -0x4b4:
        return s_WS_DirServ_DirIsFull_004dfdc8;
      case -0x4b3:
        return s_WS_DirServ_ServiceExists_004dfde0;
      case -0x4b2:
        return s_WS_DirServ_DirExists_004dfdfc;
      case -0x4b1:
        return s_WS_DirServ_ServiceNotFound_004dfe14;
      case -0x4b0:
        return s_WS_DirServ_DirNotFound_004dfe30;
      case -0x4af:
        return s_WS_DirServ_FailureStart_004dfe48;
      }
    }
    else if (param_1 < 0x2715) {
      if (param_1 == 0x2714) {
        return s_WS_WSAEINTR_004dfad8;
      }
      switch(param_1) {
      case 0:
        return s_WS_Success_004dfd0c;
      case -0x13:
        return s_WS_CommServ_ExpiredPeerCertifica_004dfae4;
      case -0x12:
        return s_WS_CommServ_BadPeerCertificate_004dfb08;
      case -0x11:
        return s_WS_CommServ_BehindFirewall_004dfb28;
      case -0x10:
        return s_WS_CommServ_InvalidMessage_004dfb44;
      case -0xf:
        return s_WS_CommServ_InvalidSequenceNumbe_004dfb60;
      case -0xe:
        return s_WS_CommServ_InvalidSessionId_004dfb84;
      case -0xd:
        return s_WS_CommServ_DecryptionFailed_004dfba4;
      case -0xc:
        return s_WS_CommServ_NotSupported_004dfbc4;
      case -0xb:
        return s_WS_CommServ_TimedOut_004dfbe0;
      case -10:
        return s_WS_CommServ_NoPortAvailable_004dfbf8;
      case -9:
        return s_WS_CommServ_ResourcesLow_004dfc14;
      case -8:
        return s_WS_CommServ_NotAuthorized_004dfc30;
      case -7:
        return s_WS_CommServ_SessionNotFound_004dfc4c;
      case -6:
        return s_WS_CommServ_MessageExceedsMax_004dfc68;
      case -5:
        return s_WS_CommServ_AlreadyExists_004dfc88;
      case -4:
        return s_WS_CommServ_InvalidParameters_004dfca4;
      case -3:
        return s_WS_CommServ_NotAllowed_004dfcc4;
      case -2:
        return s_WS_CommServ_NotAvailable_004dfcdc;
      case -1:
        return s_WS_CommServ_Failure_004dfcf8;
      }
    }
    else {
      if (param_1 == 0x2719) {
        return s_WS_WSAEBADF_004dfaac;
      }
      if (param_1 == 0x271d) {
        return s_WS_WSAEACCES_004dfab8;
      }
      if (param_1 == 0x271e) {
        return s_WS_WSAEFAULT_004dfac8;
      }
    }
  }
  else if (param_1 < 0x186c1) {
    if (param_1 == 0x186c0) {
      return s_WS_PeerAuthClient_InvalidService_004df3a0;
    }
    if (param_1 < 0x2758) {
      if (param_1 == 0x2757) {
        return s_WS_WSAEREMOTE_004df7ec;
      }
      switch(param_1) {
      case 0x2728:
        return s_WS_WSAEMFILE_004dfa8c;
      case 0x2733:
        return s_WS_WSAEWOULDBLOCK_004dfa78;
      case 0x2734:
        return s_WS_WSAEINPROGRESS_004dfa64;
      case 0x2735:
        return s_WS_WSAEALREADY_004dfa54;
      case 0x2736:
        return s_WS_WSAENOTSOCK_004dfa44;
      case 0x2737:
        return s_WS_WSAEDESTADDRREQ_004dfa30;
      case 0x2738:
        return s_WS_WSAEMSGSIZE_004dfa20;
      case 0x2739:
        return s_WS_WSAEPROTOTYPE_004dfa0c;
      case 0x273a:
        return s_WS_WSAENOPROTOOPT_004df9f8;
      case 0x273b:
        return s_WS_WSAEPROTONOSUPPORT_004df9e0;
      case 0x273c:
        return s_WS_WSAESOCKTNOSUPPORT_004df9c8;
      case 0x273d:
        return s_WS_WSAEOPNOTSUPP_004df9b4;
      case 0x273e:
        return s_WS_WSAEPFNOSUPPORT_004df9a0;
      case 0x273f:
        return s_WS_WSAEAFNOSUPPORT_004df98c;
      case 0x2740:
        return s_WS_WSAEADDRINUSE_004df978;
      case 0x2741:
        return s_WS_WSAEADDRNOTAVAIL_004df964;
      case 0x2742:
        return s_WS_WSAENETDOWN_004df954;
      case 0x2743:
        return s_WS_WSAENETUNREACH_004df940;
      case 0x2744:
        return s_WS_WSAENETRESET_004df930;
      case 0x2745:
        return s_WS_WSAECONNABORTED_004df91c;
      case 0x2746:
        return s_WS_WSAECONNRESET_004df908;
      case 0x2747:
        return s_WS_WSAENOBUFS_004df8f8;
      case 0x2748:
        return s_WS_WSAEISCONN_004df8e8;
      case 0x2749:
        return s_WS_WSAENOTCONN_004df8d8;
      case 0x274a:
        return s_WS_WSAESHUTDOWN_004df8c8;
      case 0x274b:
        return s_WS_WSAETOOMANYREFS_004df8b4;
      case 0x274c:
        return s_WS_WSAETIMEDOUT_004df8a4;
      case 0x274d:
        return s_WS_WSAECONNREFUSED_004df890;
      case 0x274e:
        return s_WS_WSAELOOP_004df884;
      case 0x274f:
        return s_WS_WSAENAMETOOLONG_004df870;
      case 0x2750:
        return s_WS_WSAEHOSTDOWN_004df860;
      case 0x2751:
        return s_WS_WSAEHOSTUNREACH_004df84c;
      case 0x2752:
        return s_WS_WSAENOTEMPTY_004df83c;
      case 0x2753:
        return s_WS_WSAEPROCLIM_004df82c;
      case 0x2754:
        return s_WS_WSAEUSERS_004df81c;
      case 0x2755:
        return s_WS_WSAEDQUOT_004df80c;
      case 0x2756:
        return s_WS_WSAESTALE_004df7fc;
      }
    }
    else if (param_1 < 0x186af) {
      if (param_1 == 0x186ae) {
        return s_WS_AsyncSocket_InvalidSocket_004df670;
      }
      if (param_1 < 0x186a6) {
        if (param_1 == 0x186a5) {
          return s_WS_AwaitingCompletion_004df744;
        }
        if (param_1 < 0x186a1) {
          if (param_1 == 100000) {
            return s_WS_Pending_004df78c;
          }
          switch(param_1) {
          case 0x276b:
            return s_WS_WSASYSNOTREADY_004df7d8;
          case 0x276c:
            return s_WS_WSAVERNOTSUPPORTED_004df7c0;
          case 0x276d:
            return s_WS_WSANOTINITIALISED_004df7a8;
          case 0x2775:
            return s_WS_WSAEDISCON_004df798;
          }
        }
        else {
          switch(param_1) {
          case 0x186a1:
            return s_WS_TimedOut_004df780;
          case 0x186a2:
            return s_WS_Killed_004df774;
          case 0x186a3:
            return s_WS_Incomplete_004df764;
          case 0x186a4:
            return s_WS_None_004df75c;
          }
        }
      }
      else {
        switch(param_1) {
        case 0x186a6:
          return s_WS_InvalidMessage_004df730;
        case 0x186a7:
          return s_WS_FailedToOpenFile_004df71c;
        case 0x186a8:
          return s_WS_FailedToWriteToFile_004df704;
        case 0x186a9:
          return s_WS_BlockMode_NotSupported_004df6e8;
        case 0x186aa:
          return s_WS_AsyncMode_NotSupported_004df6cc;
        case 0x186ab:
          return s_WS_InvalidPublicKey_004df6b8;
        case 0x186ac:
          return s_WS_MessageUnpackFailure_004df6a0;
        case 0x186ad:
          return s_WS_AuthRequired_004df690;
        }
      }
    }
    else {
      switch(param_1) {
      case 0x186af:
        return s_WS_AsyncSocket_PartialSendTo_004df650;
      case 0x186b0:
        return s_WS_AsyncSocket_StreamNotAllowed_004df630;
      case 0x186b1:
        return s_WS_AsyncSocket_DatagramNotAllowe_004df60c;
      case 0x186b2:
        return s_WS_AsyncSocket_Shutdown_004df5f4;
      case 0x186b3:
        return s_WS_AsyncSocket_ConnectFailed_004df5d4;
      case 0x186b4:
        return s_WS_SocketOp_InvalidSocket_004df5b8;
      case 0x186b5:
        return s_WS_RecvMsg_InvalidLengthFieldSiz_004df594;
      case 0x186b6:
        return s_WS_RecvMsg_InvalidMessageLength_004df574;
      case 0x186b7:
        return s_WS_PeerAuthClient_Challenge1Decr_004df548;
      case 0x186b8:
        return s_WS_PeerAuthClient_Challenge1Inva_004df518;
      case 0x186b9:
        return s_WS_PeerAuthClient_Challenge1Inva_004df4e8;
      case 0x186ba:
        return s_WS_PeerAuthClient_Challenge1Cert_004df4b0;
      case 0x186bb:
        return s_WS_PeerAuthClient_Challenge1Cert_004df478;
      case 0x186bc:
        return s_WS_PeerAuthClient_Challenge2Encr_004df44c;
      case 0x186bd:
        return s_WS_PeerAuthClient_CompleteDecryp_004df420;
      case 0x186be:
        return s_WS_PeerAuthClient_CompleteInvali_004df3f4;
      case 0x186bf:
        return s_WS_PeerAuthClient_CompleteInvali_004df3c8;
      }
    }
  }
  else {
    switch(param_1) {
    case 0x186c1:
      return s_WS_PeerAuthClient_UnexpectedChal_004df378;
    case 0x186c2:
      return s_WS_PeerAuthClient_InvalidMessage_004df354;
    case 0x186c3:
      return s_WS_PeerAuthClient_MsgUnpackFailu_004df330;
    case 0x186c4:
      return s_WS_PeerAuthServer_NotStarted_004df310;
    case 0x186c5:
      return s_WS_PeerAuthServer_InvalidService_004df2e8;
    case 0x186c6:
      return s_WS_PeerAuthServer_UnexpectedRequ_004df2c4;
    case 0x186c7:
      return s_WS_PeerAuthServer_UnexpectedChal_004df29c;
    case 0x186c8:
      return s_WS_PeerAuthServer_InvalidMessage_004df278;
    case 0x186c9:
      return s_WS_PeerAuthServer_MsgUnpackFailu_004df254;
    case 0x186ca:
      return s_WS_PeerAuthServer_InvalidAuthMod_004df230;
    case 0x186cb:
      return s_WS_PeerAuthServer_InvalidEncrypt_004df208;
    case 0x186cc:
      return s_WS_PeerAuthServer_InvalidClientC_004df1dc;
    case 0x186cd:
      return s_WS_PeerAuthServer_ExpiredClientC_004df1b0;
    case 0x186ce:
      return s_WS_PeerAuthServer_FailedToVerify_004df17c;
    case 0x186cf:
      return s_WS_PeerAuthServer_FailedToEncryp_004df148;
    case 0x186d0:
      return s_WS_PeerAuthServer_FailedToDecryp_004df118;
    case 0x186d1:
      return s_WS_PeerAuthServer_InvalidSecretA_004df0f4;
    case 0x186d2:
      return s_WS_PeerAuthServer_InvalidSecretB_004df0d0;
    case 0x186d3:
      return s_WS_PeerAuth_GetCertFailure_004df0b4;
    case 0x186d4:
      return s_WS_ServerReq_FailedAllServers_004df094;
    case 0x186d5:
      return s_WS_ServerReq_NoServersSpecified_004df074;
    case 0x186d6:
      return s_WS_ServerReq_NeedAuthContext_004df054;
    case 0x186d7:
      return s_WS_ServerReq_TryNextServer_004df038;
    case 0x186d8:
      return s_WS_ServerReq_Send_004df024;
    case 0x186d9:
      return s_WS_ServerReq_Recv_004df010;
    case 0x186da:
      return s_WS_ServerReq_ExitCommunicationLo_004defec;
    case 0x186db:
      return s_WS_ServerReq_SessionExpired_004defd0;
    case 0x186dc:
      return s_WS_ServerReq_GetCertFailure_004defb4;
    case 0x186dd:
      return s_WS_ServerReq_InvalidReplyHeader_004def94;
    case 0x186de:
      return s_WS_ServerReq_UnpackFailure_004def78;
    case 0x186df:
      return s_WS_GetCert_PubKeyEncryptFailure_004def58;
    case 0x186e0:
      return s_WS_GetCert_InvalidPubKeyReply_004def38;
    case 0x186e1:
      return s_WS_GetCert_InvalidLoginReply_004def18;
    case 0x186e2:
      return s_WS_GetCert_UnableToFindHashFile_004deef8;
    case 0x186e3:
      return s_WS_GetCert_UnexpectedLoginChalle_004deed4;
    case 0x186e4:
      return s_WS_GetCert_NeedVerifierKey_004deeb8;
    case 0x186e5:
      return s_WS_GetCert_FailedToVerifyPubKeyB_004dee90;
    case 0x186e6:
      return s_WS_GetCert_InvalidCertificate_004dee70;
    case 0x186e7:
      return s_WS_GetCert_InvalidPubKeyBlock_004dee50;
    case 0x186e8:
      return s_WS_GetCert_DecryptFailure_004dee34;
    case 0x186e9:
      return s_WS_GetCert_InvalidPrivateKey_004dee14;
    case 0x186ea:
      return s_WS_GetCert_InvalidSecretConfirm_004dedf4;
    case 0x186eb:
      return s_WS_GetCert_MissingCertificate_004dedd4;
    case 0x186ec:
      return s_WS_AuthData_SetCertificateUnpack_004dedac;
    case 0x186ed:
      return s_WS_AuthData_SetPubKeyBlockUnpack_004ded84;
    case 0x186ee:
      return s_WS_AuthData_SetCertificateVerify_004ded5c;
    case 0x186ef:
      return s_WS_AuthData_SetPrivateKeyFailed_004ded3c;
    case 0x186f0:
      return s_WS_AuthSession_EncryptFailure_004ded1c;
    case 0x186f1:
      return s_WS_AuthSession_DecryptSessionIdM_004decf4;
    case 0x186f2:
      return s_WS_AuthSession_DecryptFailure_004decd4;
    case 0x186f3:
      return s_WS_AuthSession_DecryptBadLen_004decb4;
    case 0x186f4:
      return s_WS_AuthSession_DecryptInvalidSeq_004dec88;
    case 0x186f5:
      return s_WS_AuthSession_DecryptUnpackFail_004dec64;
    case 0x186f6:
      return s_WS_ServerConnection_RecvNotAllow_004dec34;
    case 0x186f7:
      return s_WS_FTP_InvalidResponse_004dec1c;
    case 0x186f8:
      return s_WS_FTP_StatusError_004dec08;
    case 0x186f9:
      return s_WS_FTP_InvalidPasvResponse_004debec;
    case 0x186fa:
      return s_WS_HTTP_InvalidHeader_004debd4;
    case 0x186fb:
      return s_WS_HTTP_StatusError_004debc0;
    case 0x186fc:
      return s_WS_HTTP_InvalidRedirect_004deba8;
    case 0x186fd:
      return s_WS_HTTP_TooManyRedirects_004deb8c;
    case 0x186fe:
      return s_WS_GetMOTD_SysNotFound_004deb74;
    case 0x186ff:
      return s_WS_GetMOTD_GameNotFound_004deb5c;
    case 0x18700:
      return s_WS_BaseMsgRequest_NoRequest_004deb40;
    case 0x18701:
      return s_WS_BaseMsgRequest_UnpackFailure_004deb20;
    case 0x18702:
      return s_WS_BaseMsgRequest_BadHeaderType_004deb00;
    case 0x18703:
      return s_WS_RoutingOp_ReplyUnpackFailure_004deae0;
    case 0x18704:
      return s_WS_RoutingOp_DontWantReply_004deac4;
    case 0x18705:
      return s_WS_RoutingOp_NeedMoreReplies_004deaa4;
    case 0x18706:
      return s_WS_GameSpySupport_UnhandledError_004dea80;
    case 0x18707:
      return s_WS_GameSpySupport_WinSockError_004dea60;
    case 0x18708:
      return s_WS_GameSpySupport_BindError_004dea44;
    case 0x18709:
      return s_WS_GameSpySupport_DNSError_004dea28;
    case 0x1870a:
      return s_WS_GameSpySupport_ConnError_004dea0c;
    }
  }
  if ((param_1 < -0xb53) && (-3000 < param_1)) {
    FUN_004b9f62(&DAT_004ec750,(byte *)s_DBProxyServ_GameSpecificError_d_004de9ec,param_1);
    return &DAT_004ec750;
  }
  FUN_004b9f62(&DAT_004ec750,&DAT_004d6ad4,param_1);
  return &DAT_004ec750;
}


