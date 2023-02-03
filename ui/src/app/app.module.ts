import { CUSTOM_ELEMENTS_SCHEMA, NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { Service } from './../shared/service';
import { Tiles } from './tiles/tiles.module';

import { CommonModule } from '@angular/common';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { IonicModule } from '@ionic/angular';
import { NgChartsModule } from 'ng2-charts';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { Chart } from './chart/chartModule';

import { SharedModule } from 'src/shared/shared.module';


@NgModule({
  declarations: [
    AppComponent
  ],
  imports: [
    CommonModule,
    Chart,
    Tiles,
    NgChartsModule,
    BrowserModule,
    AppRoutingModule,
    IonicModule.forRoot(),
    BrowserAnimationsModule,
    SharedModule,
  ],
  providers: [
    Service,
  ],
  bootstrap: [AppComponent],
  schemas: [
    CUSTOM_ELEMENTS_SCHEMA
  ],
})
export class AppModule { }
