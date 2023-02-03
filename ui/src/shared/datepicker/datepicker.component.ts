import { Service } from 'src/shared/service';
import { Component, EventEmitter, Output, ViewChild } from '@angular/core';
import { FormControl, FormGroup } from '@angular/forms';
import { endOfDay, startOfDay } from 'date-fns';
import { MatDatepicker } from '@angular/material/datepicker';

@Component({
    selector: 'datepicker',
    templateUrl: './datepicker.component.html',
})
export class DatePickerComponent {
    @ViewChild(MatDatepicker) datepicker: MatDatepicker<Date>;

    @Output() dateChanged: EventEmitter<boolean> = new EventEmitter()

    public fromDate: Date = startOfDay(new Date())
    public toDate: Date = endOfDay(new Date());
    public range = new FormGroup({
        start: new FormControl(this.fromDate),
        end: new FormControl(this.toDate),
    });

    constructor(
        private service: Service
    ) { }

    ngOnChanges() {


        this.dateChanged.emit(true)
    }

    emit() {
        this.service.historyPeriod = {
            fromDate: startOfDay(this.range.controls['start'].value as Date),
            toDate: endOfDay(this.range.controls['end'].value as Date)
        }

        console.log("Qtetsts")
        this.dateChanged.emit(true)
    }
}
