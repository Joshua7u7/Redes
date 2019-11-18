import { Injectable } from '@angular/core';
import { ToastrService } from 'ngx-toastr';


@Injectable({
  providedIn: 'root'
})

export class NotificationsService {

  constructor(private toastr: ToastrService) { }

  success(msg: string, title: string): void {
    this.toastr.success(msg, title, {
      enableHtml: true,
      progressBar: true,
      closeButton: true,
      positionClass: 'toast-top-right',
      timeOut: 5000
    });
  }

  error(msg: string, title: string): void {
    this.toastr.error(msg, title, {
      enableHtml: true,
      progressBar: true,
      closeButton: true,
      positionClass: 'toast-top-right',
      timeOut: 5000
    });
  }

  warn(msg, title) {
    this.toastr.warning(msg, title, {
      enableHtml: true,
      progressBar: true,
      closeButton: true,
      positionClass: 'toast-top-right',
      timeOut: 5000
    });
  }

  info(msg: string, title: string): void {
    this.toastr.info(msg, title, {
      enableHtml: true,
      progressBar: true,
      closeButton: true,
      positionClass: 'toast-top-right',
      timeOut: 5000
    });
  }
}
